#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "PacketData.h"


PacketData::PacketData(size_t dataSize) {
    dataPtr = new uint8_t[dataSize];
    currentPosition = 0;
    size = (int) dataSize;
}

PacketData::~PacketData() {
    delete[] dataPtr;
}

void PacketData::appendData(const void *data, size_t length) {
    if (currentPosition >= size) {
        std::cout << "PacketData is too big for buffer!\n";
        return;
    }

    if (currentPosition + length > size) {
        std::cout << "PacketData is too big for buffer!\n";
        return;
    }

    memcpy(dataPtr + currentPosition, data, length);

    currentPosition += length;
}

void PacketData::appendBytes(int value, size_t length) {
    if (currentPosition >= size) {
        std::cout << "PacketData is too big for buffer!\n";
        return;
    }

    if (currentPosition + length > size) {
        std::cout << "PacketData is too big for buffer!\n";
        return;
    }

    memset(dataPtr + currentPosition, value, length);

    currentPosition += length;
}

int PacketData::getSize() {
    return this->size;
}

uint8_t* PacketData::getData() {
    return this->dataPtr;
}

PacketData::PacketData() {
    this->size = 0;
}

PacketData::PacketData(void *data, size_t dataSize) {
    dataPtr = new uint8_t[dataSize];
    currentPosition = 0;
    size = (int) dataSize;
    appendData(data, dataSize);
}
