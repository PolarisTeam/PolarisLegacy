#include "../Packet.h"
#include "../VariablePacketBuilder.h"

class SetAreaPacket : public Packet
{
public:
	SetAreaPacket();
	~SetAreaPacket();
	PacketData build();

public:
	VariablePacketBuilder builder;
};
