#include "Packet.h"
#include "../data/Character.h"

struct MysteryPacket
{
    PacketHeader header = PacketHeader(0xC, 0x11, 0x49, 0x0, 0x0);
    uint16_t randomDataOfDoom;
    MysteryPacket(uint16_t randomData)
    {
        randomDataOfDoom = randomData;
    }
};

struct CharacterSpawnPacket
{
    PacketHeader header;
    CharacterHeaderMaybe charHeaderMaybe;
    MysteryCharacter14 unknown_14;
    char asciiString[34]; //\0\0Character in ASCII (Rest is all zeros)
    uint16_t unknown_44;
    char unk_46[6];
    uint32_t unknown_4c;
    char unk_50[8];
    uint32_t unknown_58;
    uint32_t unknown_5C;
    uint32_t playerIdCopy;
    char unk_64[4];
    uint32_t voiceParam_unknown4;
    uint32_t voiceParam_unknown8;
    uint16_t name[16]; //TODO: Find a 16-bit consistant wchar_t.
    char unk_90[4];
    CharacterLooksParameter looksParam;
    CharacterJobParameter jobsParam;
    uint16_t currentTitle[32];
    char unk_204[2];
    char unknown_206;
    char unknown_207[101];
};

struct CharacterCreatePacket // 11-5
{
    PacketHeader header;
    char unknown_8[20]; // Usually zeros so far?
    uint16_t name[16];
    char padding[4];
    CharacterLooksParameter looks;
    CharacterJobParameter jobs;
    char unknown_footer[68];
};

struct CharacterListPacket
{ //11-3
	PacketHeader header;
	uint32_t numberOfCharacters;
	uint32_t unknown_C;
	uint32_t playerId;
	char unknown_13[0xD]; // 00 00 00 00 00 03 00 00 00 00 00 C8 C2
	uint16_t name[16];
	uint32_t padding;
	CharacterLooksParameter looks;
	CharacterJobParameter jobs;
};

class FixedLengthPacket : public Packet
{
public:
    FixedLengthPacket(void* packetPtr);
    PacketData build();

private:
    void* packetPtr;
};
