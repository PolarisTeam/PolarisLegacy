#pragma once
#include <stdint.h>
#include <string>
#include "Packet.h"

class SystemMessagePacket : public Packet {
private:
    std::string message;
    uint32_t messageType;
public:
    SystemMessagePacket(std::string message, uint32_t messageType);
    ~SystemMessagePacket();
    PacketData build();
};