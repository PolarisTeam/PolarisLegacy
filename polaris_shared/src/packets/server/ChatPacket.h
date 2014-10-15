#include "../Packet.h"
#include <string>
#include <stdint.h>

class ChatPacket : public Packet
{
public:
	ChatPacket(uint32_t senderId, std::u16string message, uint32_t channel);
	~ChatPacket();
	PacketData build();
private:
	uint32_t senderId;
	std::u16string message;
	uint32_t channel;
};
