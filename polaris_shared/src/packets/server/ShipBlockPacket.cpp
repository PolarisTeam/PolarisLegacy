#include <string.h>
#include "ShipBlockPacket.h"

ShipBlockPacket::ShipBlockPacket(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4, uint16_t port) {
    uint8_t ipBits[] = { ip1, ip2, ip3, ip4 };
    memcpy(this->ipaddr, ipBits, sizeof(ipBits));
    this->port = port;
}

ShipBlockPacket::~ShipBlockPacket() {}

PacketData ShipBlockPacket::build() {
    PacketData data;
    PacketHeader header(0x90, 0x11, 0x2C, 0x0, 0x0);
    data.appendData(&header, sizeof(header));

    data.appendBytes(0, 0x64 - sizeof(header));

    // Offset 0x64
    data.appendData(&ipaddr, 4);

    // Offset 0x68
    data.appendData(&port, 2);

    data.appendBytes(0, 0x90 - 0x6A);

    return data;
}
