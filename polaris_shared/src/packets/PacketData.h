#include <stddef.h>
#include <stdint.h>

/**
* PacketData class.
* This is used as a container for storing a PSO2Packer, it's a wrapper for a bunch of memcpy calls.
* Also, useful type data could be put here (PSO2 Strings maybe?)
* It currently needs to be done better
*/
class PacketData {
public:
    PacketData();
    PacketData(size_t dataSize);
    PacketData(void* dataPtr, size_t dataSize);
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
