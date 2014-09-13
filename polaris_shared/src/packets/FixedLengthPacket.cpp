#include "FixedLengthPacket.h"

FixedLengthPacket::FixedLengthPacket(void* packetPtr) : packetPtr(packetPtr) {
}


PacketData FixedLengthPacket::build() {
    PacketHeader* header = (PacketHeader *)packetPtr;
    PacketData data(header->length);
    data.appendData(packetPtr, header->length);

    return data;
}
