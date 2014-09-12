#include "../Packet.h"


class BlockHelloPacket : public Packet {
public:
    BlockHelloPacket(uint16 blockCode) : blockCode(blockCode) {};
    PacketData build() { return PacketData(PacketHeader(16, 3, 8, 0, 0), &blockCode,16); }
private:
    uint16_t blockCode;
};