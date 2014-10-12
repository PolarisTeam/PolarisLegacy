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

struct CharacterJobParameter {
    char unknown_0;
    char unknown_1;
    char unknown_2;
    char unknown_3;
    uint32_t unknown_4;
    uint16_t unknown_8;
    uint16_t unknown_A;
    uint32_t unknown_C;
    uint16_t unknown_10;
    uint16_t unknown_12;
    uint32_t unknown_14;
    uint16_t unknown_18;
    uint16_t unknown_1A;
    uint32_t unknown_1C;
    uint16_t unknown_20;
    uint16_t unknown_22;
    uint32_t unknown_24;
    uint16_t unknown_28;
    uint16_t unknown_2A;
    uint32_t unknown_2C;
    uint16_t unknown_30;
    uint16_t unknown_32;
    uint32_t unknown_34;
    uint16_t unknown_38;
    uint16_t unknown_3A;
    uint32_t unknown_3C;
    uint16_t unknown_40;
    uint16_t unknown_42;
    uint32_t unknown_44;
    uint16_t unknown_48;
    uint16_t unknown_4A;
    uint32_t unknown_4C;
    uint16_t unknown_50;
    uint16_t unknown_52;
    uint32_t unknown_54;
    uint16_t unknown_58;
    uint16_t unknown_5A;
    uint32_t unknown_5C;
    uint16_t unknown_60;
    uint16_t unknown_62;
    uint32_t unknown_64;
    uint32_t unknown_68;
    uint16_t unknown_6C;
    uint16_t unknown_6E;
    unsigned __int128 unknown_70;
};