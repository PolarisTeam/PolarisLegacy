struct CharBlob1
{
    // 0x1AC Big
    uint16_t nameBuffer[16];
    uint8_t padding[4] = {0, 0, 0, 0};
};

struct CharBlob2
{
    uint8_t unknown[0x230];
};

struct CharacterHeaderMaybe
{
    uint32_t playerId;
    uint32_t unknown_4;
    uint16_t unknown_8;
    uint16_t unknown_A;
};

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

struct CharacterLooksParameter
{
    char unknown_data[175];
    char unknown_AF;
};

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
    #ifdef __MSC_VER // THANKS MSVC
    unsigned __m128 unknown_70;
    #else
    unsigned __int128 unknown_70;
    #endif
};
