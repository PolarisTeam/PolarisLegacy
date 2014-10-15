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

/**
* A very simple HSV color struct
*/
struct HSVColor
{
    uint16_t hue;
    uint16_t saturation;
    uint16_t value;
};

enum CharacterRace
{
    CRACE_HUMAN = 0,
    CRACE_NEWMAN,
    CRACE_CAST,
    CRACE_DEWMAN
};

/**
* Looks Parameter for Characters and maybe actors.
* TODO: Fully document this memory area.
*/
struct CharacterLooksParameter
{
    uint8_t charData[86]; // Head and Body data
    uint16_t accData1;
    uint16_t accData2;
    uint16_t accData3;
    char unknown_4[6];
    HSVColor costumeColor;
    char unknown_5[12];
    HSVColor skinColor;
    HSVColor eyeColor;
    char unknown_6[6];
    HSVColor hairColor;
    char unknown_7[2];
    uint16_t bodyPaint;
    uint8_t emblem;
    uint8_t eyePattern;
    uint16_t eyebrows;
    uint8_t eyelashes;
    uint32_t faceVariant;
    uint8_t makeupPattern1;
    uint8_t hairstyle;
    uint16_t acc1;
    uint16_t acc2;
    uint16_t acc3;
    uint8_t makeupPattern2;
    uint16_t acc4;
    uint16_t costume;
    char unknown_8[2];
    uint8_t race;
    char unknown_9;
    uint8_t female;
    char unknown_10[5];
};
