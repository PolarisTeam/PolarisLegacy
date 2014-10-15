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
struct CharacterHeaderMaybe // 12 bytes
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
    // PACKET MAP
    // ----------------------------------------
    // Offset 14 - Voice Type
    // Offset 1A - Voice Pitch / other voice data?
    // Offset 1C - Name
    // Offset 40 - Body Data? - Seems to be all of the data related to the body type and properties, 12 bytes in length
    // Offset 58 - Face Data? - Seems to be all of the data related to the face and it's properties, 24 bytes in length
    // Offset 8E - Accessory Data 1 - 2 bytes each (Where is the 4th Accessory data?)
    // Offset 90 - Accessory Data 2
    // Offset 92 - Accessory Data 3
    // Offset 9A - Costume Color - This also appears to be HSV, so it seems the you could potentially color things beyond the predefined colors that are given in chargen
    // Offset AC - Skin Color - 4 bytes, 2 for vertical and 2 for horizontal position on the color grid?
    // Offset B8 - Eye Color
    // Offset BE - Hair Color
    // Offset C6 - Body Paint
    // Offset C8 - Emblem
    // Offset CA - Eye Pattern
    // Offset CC - Eyebrows (second byte always seems to be 27?, first byte also contains the Match Hair color flag)
    // Offset CE - Eyelashes
    // Offset D0 - Face Variant? (Seems to be 4 bytes long, the values are pretty random)
    // Offset D4 - Makeup Pattern 1
    // Offset D6 - Hairstyle
    // Offset D8 - Accessory 1 - 2 Bytes each
    // Offset DA - Accessory 2
    // Offset DC - Accessory 3
    // Offset DE - Makeup Pattern 2
    // Offset E4 - Accessory 4
    // Offset E6 - Costume
    // Offset EA - Female?
    // Offset EB - Race
    // Offset F0 - Job
    
    char unknown_1[12];
    uint8_t voiceType;
    char unknown_2[5];
    uint32_t voiceData;
    char16_t name[16];
    char unknown_3[4];
    uint8_t bodyData[12];
    char unknown_4[24];
    uint8_t faceData[24];
    char unknown_5[12];
    uint16_t accData1;
    uint16_t accData2;
    uint16_t accData3;
    char unknown_6[6];
    HSVColor costumeColor;
    char unknown_7[12];
    HSVColor skinColor;
    HSVColor eyeColor;
    char unknown_8[6]; // Another color?
    HSVColor hairColor;
    char unknown_9[2];
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
    char unknown_10[2];
    uint8_t race; // Race and gender could actually be part of CharacterJobParameter?
    char unknown_11;
    uint8_t female;
    char unknown_12[5];
    CharacterJobParameter job;
    char unknown_13[80];
};
