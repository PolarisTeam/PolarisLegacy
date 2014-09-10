#pragma once

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

    virtual PacketHeader getHeader() = 0;
    virtual void* getData() = 0;

protected:
    PacketHeader header;
    void* data;
};
