#include <string.h>
#include "VariablePacketBuilder.h"

VariablePacketBuilder::VariablePacketBuilder(uint8_t type, uint8_t subtype, uint8_t flags1, uint8_t flags2)
{
	dataPointer = new uint8_t[512];
	bufferSize = 512;
	currentPosition = 0;
	PacketHeader theHeader(0x0, type, subtype, flags1, flags2);
	appendData(&theHeader, sizeof(PacketHeader));
}

VariablePacketBuilder::~VariablePacketBuilder()
{
	delete[] dataPointer;
}

void VariablePacketBuilder::appendData(void *data, size_t size)
{
	if(currentPosition + size > bufferSize)
	{
		uint8_t* newDataPtr = new uint8_t[bufferSize + size + 100];
		memmove(newDataPtr, dataPointer, bufferSize);
		delete[] dataPointer;
		dataPointer = nullptr;
		dataPointer = newDataPtr;
		bufferSize = bufferSize + size + 100;
	}
	memcpy(dataPointer + currentPosition, data, size);
	currentPosition += size;

}

PacketData VariablePacketBuilder::getData()
{
	PacketHeader* theHeader = (PacketHeader *) dataPointer;
	theHeader->length = (uint32_t) currentPosition;
	return PacketData(dataPointer, (size_t) currentPosition);
}
