#pragma once
#include <stdint.h>

#ifdef _MSC_VER
typedef __m128 int128_t;
#else
typedef __int128 int128_t;
#endif

/**
* Struct that may or may not be only used in CharacterSpawnPacket.
* TODO: Find more things that use this and name accordingly OR move into CharacterSpawnPacket if reasonable to.
*/
struct PlayerHeader // 12 bytes
{
    uint32_t playerId;
    uint32_t unknown_4;
    uint16_t unknown_8;
    uint16_t unknown_A;
};

/**
* It's a mystery!
* TODO: Make this not a mystery.
*/
struct MysteryCharacter14
{
    uint16_t unknown_0;
    uint16_t unknown_2;
    uint16_t unknown_4;
    uint16_t unknown_6;
    uint16_t unknown_7;
    uint16_t unknown_A;
    uint16_t unknown_C;
};

/**
* Looks Parameter for Characters and maybe actors.
* TODO: Fully document this memory area.
*/
struct CharacterLooksParameter
{
    char unknown_data[175];
    char unknown_AF;
};


/**
* 'Job' (aka class) Parameters for Characters.
* TODO: Split the level entires into their own structs.
* TODO: Figure out what all the unknown values are used for.
*/
struct CharacterJobParameter
{
    char unknown_0;
    char unknown_1;
    char unknown_2;
    char unknown_3;
    uint32_t unknown_4;  // Entry 1
    uint16_t hunterLv;
    uint16_t unknown_A;
    uint32_t hunterExp;  // Entry 2
    uint16_t rangerLv;
    uint16_t unknown_12;
    uint32_t rangerExp; // Entry 3
    uint16_t forceLv;
    uint16_t unknown_1A;
    uint32_t forceExp; // Entry 4
    uint16_t fighterLv;
    uint16_t unknown_22;
    uint32_t fighterExp; // Entry 5
    uint16_t gunnerLv;
    uint16_t unknown_2A;
    uint32_t gunnerExp; // Entry 6
    uint16_t techerLv;
    uint16_t unknown_32;
    uint32_t techerExp; // Entry 7
    uint16_t braverLv;
    uint16_t unknown_3A;
    uint32_t braverExp; // Entry 8
    uint16_t bouncerLv;
    uint16_t unknown_42;
    uint32_t bouncerExp; // Entry 9
    uint16_t unknown_48;
    uint16_t unknown_4A;
    uint32_t unknown_4C; // Entry 10
    uint16_t unknown_50;
    uint16_t unknown_52;
    uint32_t unknown_54; // Entry 11
    uint16_t unknown_58;
    uint16_t unknown_5A;
    uint32_t unknown_5C; // Entry 12
    uint16_t unknown_60;
    uint16_t unknown_62;
    uint32_t unknown_64; // Not entries...?
    uint32_t unknown_68;
    uint16_t unknown_6C;
    uint16_t unknown_6E;
	int32_t unknown_70[4]; // BAD BAD BAD BAD FIXME
};
