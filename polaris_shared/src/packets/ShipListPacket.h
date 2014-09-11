#pragma once

#include "Packet.h"
#include <vector>
#include <string>

class ShipListPacket : public Packet {
public:
    struct ShipEntry {
        uint32_t number;
        uint16_t name[16];
        uint8_t ip[4];
        uint32_t zero;
        uint16_t status;
        uint16_t order;
        uint32_t unknown;
    };

    std::vector<ShipEntry> ships;

    void addShip(uint32_t number, const std::u16string name, uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint32_t status, uint32_t order, uint32_t unknown);

    PacketData build();
};

