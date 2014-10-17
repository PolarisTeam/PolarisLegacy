#include "Packet.h"
#include <array>

class VariablePacketBuilder
{
public:
	VariablePacketBuilder(uint8_t type, uint8_t subtype, uint8_t flags1, uint8_t flags2);
	~VariablePacketBuilder();
	// This may not work for arrays?
	template<typename T>
	VariablePacketBuilder & operator<< (const T& thing)
	{
		appendData((void *) &thing, sizeof(T));
		return *this;
	}
	PacketData getData();



private:
	void appendData(void*data, size_t size);
	size_t bufferSize;
	uint8_t* dataPointer;
	size_t currentPosition;

};