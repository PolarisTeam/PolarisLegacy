#include "Packet.h"

struct MysteryPacket{
    PacketHeader header = PacketHeader(0x10, 0x11, 0x49, 0x0, 0x0);
    uint16_t randomDataOfDoom;
    MysteryPacket(uint16_t randomData) {
        randomDataOfDoom = randomData;
    }
};

class FixedLengthPacket : public Packet
{
public:
    FixedLengthPacket(void* packetPtr);
    PacketData build();

private:
    void* packetPtr;
};