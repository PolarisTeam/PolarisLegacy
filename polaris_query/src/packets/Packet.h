#pragma once

#include <vector>

struct PacketHeader {
    uint32_t length;
    uint8_t command;
    uint8_t subcommand;
    uint8_t flag1;
    uint8_t flag2;
};

class Packet {
public:
    Packet() {}
    virtual ~Packet() {}
    virtual void parse(void* dataPtr, uint32_t size);
    virtual std::vector<uint8_t> build();
};