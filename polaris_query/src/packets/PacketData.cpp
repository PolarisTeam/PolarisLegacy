#include <stdlib.h>
#include <string.h>
#include "PacketData.h"


PacketData::PacketData(size_t dataSize) {
    dataPtr = malloc(dataSize);
    currentPosition = 0;
    size = dataSize;
}

PacketData::~PacketData() {
    delete dataPtr;
}

void PacketData::appendData(const void *data, size_t length) {
    if (currentPosition > size) {
        return;
    }

    if (currentPosition + length > size) {
        return;
    }

    memcpy(dataPtr + currentPosition, data, length);

    currentPosition += length;
}

int PacketData::getSize() {
    return this->size;
}

void* PacketData::getData() {
    return this->dataPtr;
}