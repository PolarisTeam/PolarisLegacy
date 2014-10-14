struct CharBlob1 {
    // 0x1AC Big
    uint16_t nameBuffer[16];
    uint8_t padding[4] = {0, 0, 0, 0};
};

struct CharBlob2 {
    uint8_t unknown[0x230];
};

struct CharacterHeaderMaybe {
    uint32_t playerId;
    uint32_t unknown_4;
    uint16_t unknown_8;
    uint16_t unknown_A;
};

struct MysteryCharacter14 {
    uint16_t unknown_0;
    uint16_t unknown_2;
    uint16_t unknown_4;
    uint16_t unknown_6;
    uint16_t unknown_7;
    uint16_t unknown_A;
    uint16_t unknown_C;
};

struct CharacterLooksParameter {
    char unknown_data[175];
    char unknown_AF;
};

struct CharJobParamEntry {
   uint32_t unknown_0;
   uint16_t unknown_4;
   uint16_t unknown_6;
};

struct CharacterJobParameter {
    char unknown_0;
    char unknown_1;
    char unknown_2;
    char unknown_3;
    CharJobPramEntry entries[12]; // I guess?
    /*uint32_t unknown_4;  // Entry 1
    uint16_t unknown_8;
    uint16_t unknown_A;
    uint32_t unknown_C;  // Entry 2
    uint16_t unknown_10;
    uint16_t unknown_12;
    uint32_t unknown_14; // Entry 3
    uint16_t unknown_18;
    uint16_t unknown_1A;
    uint32_t unknown_1C; // Entry 4
    uint16_t unknown_20;
    uint16_t unknown_22;
    uint32_t unknown_24; // Entry 5
    uint16_t unknown_28;
    uint16_t unknown_2A;
    uint32_t unknown_2C; // Entry 6
    uint16_t unknown_30;
    uint16_t unknown_32;
    uint32_t unknown_34; // Entry 7
    uint16_t unknown_38;
    uint16_t unknown_3A;
    uint32_t unknown_3C; // Entry 8
    uint16_t unknown_40;
    uint16_t unknown_42;
    uint32_t unknown_44; // Entry 9
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
    uint16_t unknown_62; */
    uint32_t unknown_64; // Not entries...?
    uint32_t unknown_68;
    uint16_t unknown_6C;
    uint16_t unknown_6E;
    #ifdef __MSVC_VER
    unsigned __m128 unknown_70;
    #else
    unsigned __int128 unknown_70;
    #endif
};
