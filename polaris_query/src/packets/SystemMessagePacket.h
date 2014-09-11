#pragma once
#include <stdint.h>
#include <string>
#include "Packet.h"

class SystemMessagePacket : public Packet {
private:
    std::basic_string<char16_t> message;
    uint32_t messageType;
public:
    SystemMessagePacket(std::basic_string<char16_t> message, uint32_t messageType);
    ~SystemMessagePacket();
    PacketData build();
};