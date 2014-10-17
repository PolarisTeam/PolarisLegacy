#include "SetAreaPacket.h"

PacketData SetAreaPacket::build()
{
	return builder.getData();
}

SetAreaPacket::SetAreaPacket() : builder(0x3, 0x24, 0x4, 0x0) {}

SetAreaPacket::~SetAreaPacket()
{

}
