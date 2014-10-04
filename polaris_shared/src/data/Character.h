#include <bits/stringfwd.h>

struct CharBlob1 {
    // 0x1AC Big
    uint16_t nameBuffer[16];
    uint8_t padding[4] = {0, 0, 0, 0};


};

struct CharBlob2 {
// 0x230 Big
    uint8_t unknown[0x230];
};

class Character {
public:
    Character();
    ~Character();

public: //For now
    std::u16string name;



};