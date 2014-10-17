#pragma once

#include <stddef.h>
#include <stdint.h>
#include "Packet.h"

struct PacketHeader;

/**
* PacketData class.
* This is used as a container for storing a PSO2Packet, it's a wrapper for a bunch of memcpy calls.
* It may or may not need more work
*/
class PacketData 
{
public:
    PacketData();
    PacketData(size_t dataSize);
    PacketData(PacketHeader header, void* data);
	PacketData(void* data, size_t length);
	template <class C>
	PacketData(C& thing)
	{
		PacketData(&thing, sizeof(C));
	}
    ~PacketData();
    void appendData(const void* data, size_t length);
    void appendBytes(int value, size_t length);
    int getSize();
    uint8_t* getData();

private:
    int size;
    int currentPosition;
    uint8_t* dataPtr;
};
