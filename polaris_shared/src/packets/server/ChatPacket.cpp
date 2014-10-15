#include "ChatPacket.h"
#include "../../data/Character.h"
#include "../../data/PSO2String.h"

ChatPacket::ChatPacket(uint32_t senderId, std::u16string message, uint32_t channel) : senderId(senderId), message(message), channel(channel)
{

}

ChatPacket::~ChatPacket()
{

}

PacketData ChatPacket::build()
{
	Polaris::Data::PSO2String string = Polaris::Data::CreatePSO2String(message, 0xa2, 0x78f7);
	PacketHeader header(8 + sizeof(PlayerHeader) + (sizeof(uint32_t) * 2) + string.dataLength, 0x7, 0x0, 0x44, 0x0);
	PacketData data(header.length);
	data.appendData(&header, sizeof(PacketHeader));
	PlayerHeader pHeader;
	pHeader.playerId = senderId;
	pHeader.unknown_4 = 0;
	pHeader.unknown_8 = 0;
	pHeader.unknown_A = 0;
	data.appendData(&pHeader, sizeof(PlayerHeader));
	data.appendData(&channel, sizeof(uint32_t));

	data.appendData(&string.magicValue, sizeof(uint32_t));
	data.appendData(string.utf16string.data(), string.dataLength);

	return data;
}
