#include "ShipListPacket.h"
#include <time.h>


PacketData ShipListPacket::build() {
    PacketData data(sizeof(PacketHeader) + 12 + (sizeof(ShipEntry) * ships.size()));

    PacketHeader header(data.getSize(), 0x11, 0x3D, 4, 0);
    uint32_t count = (ships.size() + 81) ^ 0xE418;
    uint32_t timestamp = time(NULL);
    uint32_t footerValue = 1;

    data.appendData(&header, sizeof(header));
    data.appendData(&count, 4);

    for (const ShipEntry &entry : ships) {
        data.appendData(&entry, sizeof(entry));
    }

    data.appendData(&timestamp, 4);
    data.appendData(&footerValue, 4);

    return data;
}


void ShipListPacket::addShip(uint32_t number, const std::u16string name, uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint32_t status, uint32_t order, uint32_t unknown) {
    ShipEntry entry;

    entry.number = number;
    entry.zero = 0;
    entry.status = status;
    entry.order = order;
    entry.unknown = unknown;

    for (int i = 0; i < 16; i++) {
        if (i < name.size())
            entry.name[i] = name[i];
        else
            entry.name[i] = 0;
    }

    entry.ip[0] = ip0;
    entry.ip[1] = ip1;
    entry.ip[2] = ip2;
    entry.ip[3] = ip3;

    ships.push_back(entry);
}


