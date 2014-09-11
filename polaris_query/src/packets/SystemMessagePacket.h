#pragma once
#include <stdint.h>
#include <string>
#include "Packet.h"

class SystemMessagePacket : public Packet {
private:
    char const *message;
    uint32_t messageType;
public:
    SystemMessagePacket(char const *message, uint32_t messageType);
    ~SystemMessagePacket();
    PacketData build();
};