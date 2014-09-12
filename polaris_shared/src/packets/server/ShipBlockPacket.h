#include "../Packet.h"

class ShipBlockPacket : public Packet {
public:
    ShipBlockPacket(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4, uint16_t port);
    ~ShipBlockPacket();
    PacketData build();
private:
    uint8_t ipaddr[4];
    uint16_t port;
};
