#include "../Packet.h"


class BlockHelloPacket : public Packet {
public:
    BlockHelloPacket(uint16_t blockCode) {
        data[0] = 3;
        data[1] = blockCode;
        data[2] = 0;
        data[3] = 0;
    }
    PacketData build() {
        return PacketData(PacketHeader(16, 3, 8, 0, 0), &data);
    }
private:
    uint16_t data[4];
};
