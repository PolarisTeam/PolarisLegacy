#include <packets/Packet.h>
#include "packets/server/BlockHelloPacket.h"
#include "Poco/Crypto/RSAKey.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Glob.h"
#include <string.h>
#include <packets/FixedLengthPacket.h>
#include <fstream>
#include <ctime>
#include <packets/server/LoginResponse.h>
#include "PolarisConnection.h"
#include "PolarisClient.h"
#include "Poco/Util/Application.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "RandomHelper.h"

PolarisConnection::PolarisConnection(const StreamSocket& socket, SocketReactor& reactor):
    socket(socket),
    reactor(reactor),
    bufferPtr(new uint8_t[BUFFER_SIZE]),
    bufferPosition(0),
    outputTransform(0), inputTransform(0),
    connTime(std::time(NULL))
{
    this->client = new PolarisClient(this);

    reactor.addEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.addEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));

    Poco::Util::Application::instance().logger().information("New client connected, saying hello!");

    BlockHelloPacket hello(201); // TODO Dynamic block pls
    PacketData helloData = hello.build();
    sendPacket(helloData);
}

PolarisConnection::~PolarisConnection()
{
    delete this->client;
    delete[] this->bufferPtr;

    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));

    delete outputTransform;
    delete inputTransform;
}

void PolarisConnection::onShutdown(AutoPtr<ShutdownNotification> const &notification)
{
    Poco::Util::Application::instance().logger().information("Lost connection to client.");
    delete this;
}

void PolarisConnection::onReadable(AutoPtr<ReadableNotification> const &notification)
{
    /*
    1. Check if buffer already has data, if so deal with that
    2. No data, new packet, read header
    3. ...things?
    */

    // Fill up the buffer, as much as possible
    int readAmount;

    if (inputTransform) {
        uint8_t encrypted[BUFFER_SIZE];
        readAmount = socket.receiveBytes(encrypted, BUFFER_SIZE - bufferPosition);
        inputTransform->transform(encrypted, readAmount, &bufferPtr[bufferPosition], readAmount);
    } else {
        readAmount = socket.receiveBytes(&bufferPtr[bufferPosition], BUFFER_SIZE - bufferPosition);
    }
    bufferPosition += readAmount;

    if (readAmount <= 0) {
        // Connection failed
        delete this;
        return;
    }

    // Enough to process?
    int position = 0;

    while ((position + 4) <= bufferPosition) {
        uint32_t packetSize = *((uint32_t *)&bufferPtr[position]);
        if ((position + packetSize) > bufferPosition) {
            // This packet is unfinished, bail out
            break;
        }

        handlePacket(&bufferPtr[position]);
        position += packetSize;
    }

    // If we handled any packets, we must remove their data from the buffer
    if (position > 0) {
        if (position >= bufferPosition) {
            // End was reached, just empty the thing out.
            bufferPosition = 0;
        } else {
            // Some data remains, move it to the beginning
            memmove(bufferPtr, &bufferPtr[position], bufferPosition - position);
            bufferPosition -= position;
        }
    }
}


void PolarisConnection::sendPacket(PacketData &data)
{
    packetCount++;
    PacketHeader *header = (PacketHeader *)data.getData();
    Poco::Util::Application::instance().logger().information(Polaris::string_format("[Sending packet : %d bytes, type %x-%x]", header->length, header->command, header->subcommand));

    // Save packet to disk
    Poco::File folder(Polaris::string_format("packets/%i/", connTime));
    folder.createDirectories();
    Poco::FileOutputStream packetFileWriter(Polaris::string_format("packets/%i/%i.%x-%x.S.bin", connTime, packetCount, header->command, header->subcommand));
    packetFileWriter.write((char const *) data.getData(), header->length);
    packetFileWriter.flush();
    packetFileWriter.close();

    if (outputTransform)
    {
        uint8_t *encoded = new uint8_t[data.getSize()];
        this->outputTransform->transform(data.getData(), data.getSize(), encoded, data.getSize());
        this->socket.sendBytes(encoded, data.getSize());
        delete[] encoded;
    }
    else
    {
        this->socket.sendBytes(data.getData(), data.getSize());
    }
}


void PolarisConnection::handlePacket(uint8_t *packet)
{
    PacketHeader *header = (PacketHeader *)packet;

    // Incomplete (corrupted/malicious?) packet
    if (header->length < 8)
        return;

    packetCount++;
    Poco::Util::Application::instance().logger().information(Polaris::string_format("[Received packet : %d bytes, type %x-%x]", header->length, header->command, header->subcommand));
    Poco::File folder(Polaris::string_format("packets/%i/", connTime));
    folder.createDirectories();
    Poco::FileOutputStream packetFileWriter(Polaris::string_format("packets/%i/%i.%x-%x.C.bin", connTime, packetCount, header->command, header->subcommand));
    packetFileWriter.write((char const *) packet, header->length);
    packetFileWriter.flush();
    packetFileWriter.close();

    // Key Exchange
    if (header->command == 0x11 && header->subcommand == 0x0B)
    {
        // Key exchange
        handleKeyExchange(packet);
        return;
    }

    // Login Packet
    if (header->command == 0x11 && header->subcommand == 0x00)
    {
        MysteryPacket mystery(5);
        PacketData flp = FixedLengthPacket(&mystery).build();
        sendPacket(flp);

        //PacketData welcomeMsg(SystemMessagePacket(u"This has not been implemented yet.\nThank you for connecting to a PolarisServer.", 0x1).build());
        //sendPacket(welcomeMsg);
        PacketData lResponse(LoginResponsePacket(u"", u"B001-DarkFox").build());
        sendPacket(lResponse);

        // YOLOSWAG
        std::string yolo = "Ini.ControlSetting={LobbyAction={A=\"clap\",C=\"sit2\",B=\"bow\",E=\"yell\",D=\"dance1\",G=\"guts\",F=\"dance2\",I=\"\",H=\"pose1\",K=\"kiss\",J=\"pose2\",M=\"monomane\",L=\"laugh\",O=\"\",N=\"no\",Q=\"howareyou\",P=\"chair_oran\",S=\"sorry\",R=\"salute\",U=\"you\",T=\"praise\",W=\"wave\",V=\"provoke\",Y=\"yes\",X=\"sit1\",Z=\"greet\",},MainInputType=0,LoginCall=true,PadBehavior={AnalogSetting={L={Direction=\"Plus\",ChangeSign=false,Axis=\"Z\",},R={Direction=\"Minus\",ChangeSign=true,Axis=\"Z\",},X2={Direction=\"Both\",ChangeSign=false,Axis=\"Rx\",},Y2={Direction=\"Both\",ChangeSign=false,Axis=\"Ry\",},Y1={Direction=\"Both\",ChangeSign=false,Axis=\"Y\",},X1={Direction=\"Both\",ChangeSign=false,Axis=\"X\",},},DigitalSetting={A=1,B18=16,B15=13,B=0,RThumb=9,B21=19,B19=17,B14=12,L=4,B20=18,LThumb=8,B17=15,R=5,Select=6,X=2,Y=3,B16=14,ThresR=15,B22=22,Start=7,ThresL=14,R2=-1,L2=-1,},},MouseCtrl={MouseActionWheel={Wheel=\"ChangeMainPalette\",},MouseActionLR={R=\"PhotonArts\",L=\"NormalAttack\",},Presets={[1]=\"RRcm\",[2]=\"RRcm\",},Window={X2=\"\",R=\"CloseForm\",M=\"\",X1=\"\",},MouseActionM={M=\"SelectMenu\",X2=\"\",X1=\"\",},},PadCtrl={NormalView={PhotonArts=\"Y\",PaletteForce=\"PovExactD\",LockOnNext=\"\",PaletteReverse=\"PovExactU\",ChangeAreaMap=\"LThumb\",SubPalette=\"ThresL\",SubPaletteLeft=\"PovExactL\",Jump=\"B\",AutoRun=\"\",MainMenu=\"Start\",NormalAttack=\"X\",WeaponAction=\"R\",ChangeView=\"\",SelectMenu=\"Select\",Access=\"A\",Avoid=\"ThresR\",LockOn=\"L\",SubPaletteRight=\"PovExactR\",ChangeRadarMap=\"RThumb\",},Window={Cancel=\"B\",ChangeCtrlWindowBack=\"\",Decide=\"A\",Exception=\"RThumb\",TabBack=\"L\",AllWindowClose=\"Start\",Function=\"X\",NextWidget=\"Y\",PageForward=\"\",MultiSelect=\"ThresR\",PageBack=\"\",NextTabDetails=\"Select\",TabForward=\"R\",ChangeCtrlWindowForward=\"ThresL\",},ShoulderView={SubPaletteLeft=\"PovExactL\",PhotonArts=\"Y\",Jump=\"B\",AutoRun=\"\",MainMenu=\"Start\",Access=\"A\",Avoid=\"ThresR\",SelectMenu=\"Select\",ChangeView=\"RThumb\",PaletteReverse=\"PovExactU\",WeaponAction=\"R\",NormalAttack=\"X\",SubPalette=\"ThresL\",SubPaletteRight=\"PovExactR\",PaletteForce=\"PovExactD\",},Presets={[2]=\"RZViewRcm\",[1]=\"Custom\",[3]=\"Rcm1\",},},KeyboardCtrl={Shortcut={RunSubPalette=\"1\",ChangeMainPalette=\"3\",RunWindowShortcut=\"2\",RunShortcutWord=\"4\",},Presets={[2]=\"RZViewRcm\",[3]=\"Rcm1\",[1]=\"RNViewRcm\",[4]=\"Rcm1\",[5]=\"Custom\",[9]=\"Custom\",},WindowShortcutFunc={WindowShortcut8=\"13\",WindowShortcut9=\"2\",WindowShortcut3=\"4\",WindowShortcut1=\"1\",WindowShortcut5=\"7\",WindowShortcut4=\"5\",WindowShortcut0=\"19\",WindowShortcut2=\"3\",WindowShortcut7=\"9\",WindowShortcut6=\"8\",},Window={Cancel=\"LBracket\",Decide=\"Return\",TabBack=\"Comma\",MultiSelect=\"Shift\",ChangeCtrlWindowForward=\"Numpad1\",NextWidget=\"Tab\",MoveSelection=\"Tab\",NextTabDetails=\"Q\",TabForward=\"Period\",ChangeCtrlWindowBack=\"Numpad3\",},NormalView={Access=\"E\",OpenPayShop=\"\",OpenPlayerList=\"\",PaletteForce=\"F\",OpenLicense=\"\",ChangeMouseMode=\"T\",ChatStartParty=\"P\",PaletteReverse=\"R\",ChangeAreaMap=\"N\",OpenMail=\"\",ChatStart=\"Return\",OpenWeapon=\"\",OpenCharaInfo=\"\",SubPaletteLeft=\"G\",OpenRentalLimit=\"\",OpenFriend=\"\",Jump=\"Space\",MainMenu=\"\",ChangeRadarMap=\"M\",OpenProfile=\"\",ChatStartWhisper=\"L\",CameraUp=\"Divide\",ChangeView=\"Z\",WeaponAction=\"Shift\",OpenLogOut=\"F12\",OpenClientOrder=\"\",LockOn=\"Q\",MoveRight=\"D\",OpenQuestInfo=\"\",PhotonArts=\"Backslash\",OpenCustomize=\"U\",MoveLeft=\"A\",OpenMyMenu=\"\",OpenEventItem=\"\",OpenMag=\"Y\",LockOnNext=\"\",ChatStartGuild=\"O\",CameraDown=\"Multiply\",MoveForward=\"W\",MoveBack=\"S\",OpenArmor=\"\",CameraNear=\"Subtract\",SubPalette=\"B\",OpenConfig=\"\",OpenGuild=\"\",OpenMatterBoard=\"\",OpenSubPalette=\"J\",OpenParty=\"\",OpenCommunicationLog=\"\",Avoid=\"X\",AutoRun=\"V\",OpenItemPack=\"I\",OpenPayLog=\"\",OpenSymbolArt=\"\",NormalAttack=\"Slash\",SelectMenu=\"\",OpenAcGacha=\"F11\",ChatStartPublic=\"Semicolon\",CameraFar=\"Add\",SubPaletteRight=\"H\",OpenMacro=\"\",},ShoulderView={MoveForward=\"W\",OpenPayShop=\"\",OpenPlayerList=\"\",MainMenu=\"\",OpenLicense=\"\",ChangeMouseMode=\"T\",ChatStartParty=\"P\",PaletteReverse=\"R\",ChangeAreaMap=\"N\",OpenMail=\"\",ChatStart=\"Return\",OpenWeapon=\"\",OpenCharaInfo=\"\",SubPaletteLeft=\"G\",OpenRentalLimit=\"\",OpenFriend=\"\",Jump=\"Space\",OpenMacro=\"\",ChangeRadarMap=\"M\",OpenProfile=\"\",ChatStartWhisper=\"L\",Access=\"E\",ChangeView=\"Z\",OpenAcGacha=\"F11\",OpenQuestInfo=\"\",OpenClientOrder=\"\",LockOn=\"Q\",MoveRight=\"D\",OpenLogOut=\"F12\",PhotonArts=\"Backslash\",OpenCustomize=\"U\",NormalAttack=\"Slash\",OpenMyMenu=\"\",OpenEventItem=\"\",OpenMag=\"Y\",LockOnNext=\"\",ChatStartGuild=\"O\",CameraDown=\"\",WeaponAction=\"Shift\",MoveBack=\"S\",OpenArmor=\"\",CameraNear=\"\",SubPalette=\"B\",OpenConfig=\"\",OpenGuild=\"\",OpenMatterBoard=\"\",OpenSubPalette=\"J\",OpenParty=\"\",OpenCommunicationLog=\"\",Avoid=\"X\",AutoRun=\"V\",OpenItemPack=\"I\",OpenPayLog=\"\",OpenSymbolArt=\"\",MoveLeft=\"A\",SelectMenu=\"\",CameraUp=\"\",ChatStartPublic=\"Semicolon\",PaletteForce=\"F\",SubPaletteRight=\"H\",CameraFar=\"\",},},Announce={Type=3,},IgnoreBeginnerBlock=false,}\n\0";
        uint32_t swag = (uint32_t) (((yolo.size() + 1) + 0x100) ^ 0x54AF);
        PacketHeader swagHeader(8 + (yolo.length() + 1) + sizeof(swag), 0x2B, 0x02, 0x4, 0x0);
        PacketData yoloPacket(swagHeader.length);
        yoloPacket.appendData(&swagHeader, sizeof(PacketHeader));
        yoloPacket.appendData(&swag, 4);
        yoloPacket.appendData(yolo.data(), yolo.size() + 1);
        sendPacket(yoloPacket);
    }

    // Character list request
    if (header->command == 0x11 && header->subcommand == 0x02)
    {
		CharacterListPacket clp = {};
		clp.header = PacketHeader(sizeof(CharacterListPacket), 0x11, 0x03, 0x0, 0x0);
		clp.numberOfCharacters = 0;
		PacketData clpPkt(sizeof(clp));
		clpPkt.appendData(&clp, sizeof(clp));

		sendPacket(clpPkt);
    }

    // Character selected...
    if (header->command == 0x11 && header->subcommand == 0x04)
    {
        // Load in the loading screen state
        PacketHeader newState(0x10, 0x16, 0x01, 0x4, 0x0);
        PacketData newData(newState.length);
        newData.appendData(&newState, sizeof(PacketHeader));
        char payload[8] = {0, 0, 0, 0, (char) 0xb2, 0x3f, 0, 0};
        newData.appendData(&payload, 8);
        sendPacket(newData);
        
        // Tell the state to move on...
        PacketData moveOver(8);
        PacketHeader moveOverHeader(0x8, 0x3, 0x4, 0x0, 0x0);
        moveOver.appendData(&moveOverHeader, sizeof(moveOverHeader));
        sendPacket(moveOver);
    }

    if (header->command == 0x3 && header->subcommand == 0x3)
    {
        playbackPackets("sampleset", 70, 70, 0); // TODO: Set Area

        PacketData setPlayerID(0x14);
        PacketHeader setPlayerIDHeader(0x14, 0x6, 0x0, 0x0, 0x0);
        setPlayerID.appendData(&setPlayerIDHeader, sizeof(PacketHeader));
        setPlayerID.appendData(&(this->client->player_id), sizeof(uint32_t));
        setPlayerID.appendBytes(0, 4);
        setPlayerID.appendBytes(4, 1);
        setPlayerID.appendBytes(0, 3);
        sendPacket(setPlayerID); // Set player ID.

        playbackPackets("sampleset", 103, 104, 1); // TODO: Set player data

        PacketData unlockControls(0x8);
        PacketHeader unlockHeader(0x8, 0x3, 0x2b, 0x0, 0x0);
        unlockControls.appendData(&unlockHeader, 0x8);
        sendPacket(unlockControls); // Unlock player movement.
    }

    if (header->command == 0x3 && header->subcommand == 0x10)
    {
        PacketHeader doItMaybe(0x8, 0x3, 0x23, 0x0, 0x0);
        PacketData doItPacket(0x8);
        doItPacket.appendData(&doItMaybe, 0x8);
        sendPacket(doItPacket);
    }

    if (header->command == 0x7 && header->subcommand == 0x00)
    {
        char16_t messageData[(header->length - 0x1c) / 2];
        memcpy((void *) &messageData, packet + 0x1C, header->length - 0x1C);
        std::u16string message(messageData);
        Poco::Util::Application::instance().logger().information(Polaris::string_format("CHAT: %ls", message.data()));
        playbackPackets("sampleset", 794, 1177, 1);
    }

    // Character creator request
    if (header->command == 0x11 && header->subcommand == 0x41)
    {
        PacketHeader yay(0x18, 0x11, 0x42, 0x0, 0x0);
        PacketData yayPkt(yay.length);
        yayPkt.appendData(&yay, sizeof(yay));
        yayPkt.appendBytes(0, 0x18 - sizeof(yay));
        sendPacket(yayPkt);
    }

    // Character creator request 2
    if (header->command == 0x11 && header->subcommand == 0x54)
    {
        PacketHeader yay2(0xC, 0x11, 0x55, 0x0, 0x0);
        PacketData yayPkt2(yay2.length);
        yayPkt2.appendData(&yay2, sizeof(yay2));
        yayPkt2.appendBytes(0, 0xC - sizeof(yay2));
        sendPacket(yayPkt2);
    }
}

void PolarisConnection::handleKeyExchange(uint8_t *packet)
{
    PacketHeader *header = (PacketHeader *)packet;

    if (header->length < 0x88)
        return;

    // Cache this key at some point.. maybe?
    Cipher *rsa = 0;
    CryptoTransform *dec = 0;

    try
    {
        RSAKey rsaKey("", "privateKey.pem");
        rsa = CipherFactory::defaultFactory().createCipher(rsaKey);
        dec = rsa->createDecryptor();

        // Reverse the input (encrypted) data
        uint8_t input[0x80], output[0x80];
        for (int i = 0; i < 0x80; i++)
            input[i] = packet[0x87 - i];

        int processed = dec->transform(input, sizeof(input), output, sizeof(output));
        processed += dec->finalize(output, sizeof(output) - processed);

        if (processed >= 0x20)
        {
            // Valid key exchange
            // First 16 bytes: Challenge data, encrypted with RC4 key
            // Following 16 bytes: RC4 key

            std::vector<uint8_t> rc4key(16), rc4iv;
            memcpy(rc4key.data(), &output[16], 16);

            CipherKey rc4ck("rc4", rc4key, rc4iv);
            cipher = CipherFactory::defaultFactory().createCipher(rc4ck);

            // First off, generate the response to activate the client
            CryptoTransform *dec = cipher->createDecryptor();

            uint8_t response[16];
            dec->transform(output, 16, response, 16);

            delete dec;

            // Second, enable RC4 encryption on this connection
            if (outputTransform)
                delete outputTransform;
            if (inputTransform)
                delete inputTransform;
            outputTransform = cipher->createEncryptor();
            inputTransform = cipher->createDecryptor();

            // Build the response packet
            PacketData responsePacket(PacketHeader(0x18, 0x11, 0xC, 0, 0), response);
            sendPacket(responsePacket);
        }

    }
    catch (Poco::Exception &e)
    {
        Poco::Util::Application::instance().logger().error(Polaris::string_format("[Key exchange error: %s]", e.displayText().c_str()));
        socket.close();
    }

    if (rsa)
        rsa->release();
    
    delete dec;
}

void PolarisConnection::playbackPackets(std::string folder, int startPkt, int endPkt, int sleeptime)
{
    Poco::File pktFolder(folder);
    if (!pktFolder.exists())
    {
        Poco::Util::Application::instance().logger().error(Polaris::string_format("Unable to find packet folder %s for packet playback. Aborting.", folder.c_str()));
        return;
    }

    if (startPkt > endPkt)
    {
        Poco::Util::Application::instance().logger().error("startPkt > endPkt?!");
        return;
    }

    for (int i = startPkt; i <= endPkt; i++)
    {
        std::set<std::string> files;
        Poco::Glob::glob(Polaris::string_format("%s/%i.*.bin", folder.c_str(), i), files, 0);

        if (files.size() > 0)
        {
            std::set<std::string>::iterator setBegin = files.begin();
            std::string packetFileName = *setBegin;

            //FIXME: Lol stdio, we should likely use poco shit for this.
            FILE * packetFile = fopen(packetFileName.c_str(), "rb"); // DAT c_str THO
            fseek(packetFile, 0, SEEK_END);
            long packetFileSize = ftell(packetFile);
            fseek(packetFile, 0, SEEK_SET);

            char * packetFileBuffer = new char[packetFileSize];
            fread(packetFileBuffer, 1, (size_t) packetFileSize, packetFile);
            fclose(packetFile);

            PacketData packetData((size_t) packetFileSize);
            packetData.appendData(packetFileBuffer, (size_t) packetFileSize);
            Poco::Util::Application::instance().logger().information(Polaris::string_format("Sending packet file %s...", packetFileName.c_str()));
            sleep(sleeptime);
            sendPacket(packetData);

            delete[] packetFileBuffer;
        }
    }
}
