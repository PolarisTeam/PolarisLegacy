#pragma once

#include <vector>

struct PacketHeader {
    uint32_t length;
    uint8_t command;
    uint8_t subcommand;
    uint8_t flag1;
    uint8_t flag2;
    PacketHeader(uint32_t length, uint8_t command, uint8_t subcommand, uint8_t flag1, uint8_t flag2) {
        this->length = length;
        this->command = command;
        this->subcommand = subcommand;
        this->flag1 = flag1;
        this->flag2 = flag2;
    }
};

class Packet {
public:
    Packet() {}
    virtual ~Packet() {}
    virtual void parse(void* dataPtr, uint32_t size);
    virtual std::vector<uint8_t> build();
};
