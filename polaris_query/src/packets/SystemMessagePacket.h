#pragma once
#include <stdint.h>
#include <string>
#include "Packet.h"

class SystemMessagePacket : public Packet {
private:
    std::wstring message;
    uint32_t messageType;
public:
    SystemMessagePacket(std::wstring message, uint32_t messageType);
    ~SystemMessagePacket();
    PacketHeader getHeader();
    void* getData();
};