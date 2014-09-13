#include <packets/Packet.h>
#include "packets/server/BlockHelloPacket.h"
#include "Poco/Crypto/RSAKey.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/CipherFactory.h"
#include <string.h>
#include "PolarisConnection.h"
#include "PolarisClient.h"

PolarisConnection::PolarisConnection(const StreamSocket& socket, SocketReactor& reactor):
    socket(socket),
    reactor(reactor),
    bufferPtr(new uint8_t[BUFFER_SIZE]),
    bufferPosition(0),
    outputTransform(0), inputTransform(0)
{
    this->client = new PolarisClient(this);

    reactor.addEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.addEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));

    BlockHelloPacket hello(201); // TODO Dynamic block pls
    PacketData helloData = hello.build();
    sendPacket(helloData);
}

PolarisConnection::~PolarisConnection() {
    delete this->client;
    delete[] this->bufferPtr;

    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));

    delete outputTransform;
    delete inputTransform;
}

void PolarisConnection::onShutdown(AutoPtr<ShutdownNotification> const &notification) {
    delete this;
}

void PolarisConnection::onReadable(AutoPtr<ReadableNotification> const &notification) {
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


void PolarisConnection::sendPacket(PacketData &data) {
    PacketHeader *header = (PacketHeader *)data.getData();
    printf("[Sending packet : %d bytes, type %x-%x]\n", header->length, header->command, header->subcommand);

    if (outputTransform) {
        uint8_t *encoded = new uint8_t[data.getSize()];
        this->outputTransform->transform(data.getData(), data.getSize(), encoded, data.getSize());
        this->socket.sendBytes(encoded, data.getSize());
        delete[] encoded;
    } else {
        this->socket.sendBytes(data.getData(), data.getSize());
    }
}


void PolarisConnection::handlePacket(uint8_t *packet) {
    PacketHeader *header = (PacketHeader *)packet;

    // Incomplete (corrupted/malicious?) packet
    if (header->length < 8)
        return;

    printf("[Received packet : %d bytes, type %x-%x]\n", header->length, header->command, header->subcommand);

    if (header->command == 0x11 && header->subcommand == 0xB) {
        // Key exchange
        handleKeyExchange(packet);
        return;
    }
}


void PolarisConnection::handleKeyExchange(uint8_t *packet) {
    PacketHeader *header = (PacketHeader *)packet;

    if (header->length < 0x88)
        return;

    // Cache this key at some point.. maybe?
    Cipher *rsa = 0;
    CryptoTransform *dec = 0;

    try {
        RSAKey rsaKey("", "privateKey.pem");
        rsa = CipherFactory::defaultFactory().createCipher(rsaKey);
        dec = rsa->createDecryptor();

        // Reverse the input (encrypted) data
        uint8_t input[0x80], output[0x80];
        for (int i = 0; i < 0x80; i++)
            input[i] = packet[0x87 - i];

        int processed = dec->transform(input, sizeof(input), output, sizeof(output));
        processed += dec->finalize(output, sizeof(output) - processed);

        if (processed >= 0x20) {
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

    } catch (Poco::Exception &e) {
        printf("[Key exchange error:]\n%s\n", e.displayText().c_str());
    }

    if (rsa)
        rsa->release();
    delete dec;
}

