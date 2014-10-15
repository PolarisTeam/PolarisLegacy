#include "Packet.h"
#include "../data/Character.h"

#if defined (__MINGW32__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define ATTRPACK __attribute__((packed, gcc_struct))
#else
#define ATTRPACK __attribute__((packed))
#endif

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
    PacketHeader header; 					// 8 bytes
    PlayerHeader charHeaderMaybe;	// 12 bytes
    MysteryCharacter14 spawnPosition;		// 14 bytes
    char asciiString[34]; 					// 34 bytes
    uint16_t unknown_44;					// 2 bytes
	char unk_48[2];							// 6 bytes
	uint32_t unknown_4A;
    uint32_t unknown_4c;					// 4 bytes
	uint32_t unknown_50;
    char unk_54[4];							// 4 bytes
    uint32_t unknown_58;					// 4 bytes
    uint16_t unknown_5C;					// 4 bytes
	uint16_t unknown_5E;
    uint32_t playerIdCopy;					// 4 bytes
    char unk_64[4];							// 4 bytes and it's a char array ugggghhhhh
    uint32_t voiceParam_unknown4;			// 4 bytes
    uint32_t voiceParam_unknown8;			// 4 bytes
    char16_t name[16];						// 32 bytes
    char unk_90[4];							// 4 bytes
    CharacterLooksParameter looksParam;		// 176 bytes
    CharacterJobParameter jobsParam;		// 128 bytes
    uint16_t currentTitle[32];				// 64 bytes
    char unk_204[2];						// 2 bytes
    char unknown_206;						// 1 byte :|
    char unknown_207[101];					// 101 bytes
	CharacterSpawnPacket() : header(PacketHeader(sizeof(CharacterSpawnPacket), 0x8, 0x4, 0x0, 0x0)) {}
} ATTRPACK;

struct CharacterCreatePacket // 11-5
{
    PacketHeader header;
    char unknown_8[12];
    uint8_t voiceType;
    char unknown_A[5];
    uint16_t voiceData;
    char16_t name[16];
    char padding[4];
    CharacterLooksParameter looks;
    CharacterJobParameter jobs;
    char unknown_footer[68];
	CharacterCreatePacket() : header(PacketHeader(sizeof(CharacterCreatePacket), 0x11, 0x5, 0x0, 0x0)) {}
} ATTRPACK;

struct CharacterListPacket
{ //11-3
	PacketHeader header;
	uint32_t numberOfCharacters;
	uint32_t characterId = 0;
	uint32_t playerId = 0;
	uint8_t unknown_13[0xC] = {00, 00, 00, 00, 03, 00, 00, 00, 00, 00, 0xC8, 0xC2}; // 00 00 00 00 00 03 00 00 00 00 00 C8 C2
	char16_t name[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint32_t padding = 0;
	CharacterLooksParameter looks;
	CharacterJobParameter jobs;
	CharacterListPacket() : header(PacketHeader(sizeof(CharacterListPacket), 0x11, 0x3, 0x0, 0x0)) {}
} ATTRPACK;

class FixedLengthPacket : public Packet
{
public:
    FixedLengthPacket(void* packetPtr);
    PacketData build();

private:
    void* packetPtr;
};
