#include <stddef.h>
#include <stdint.h>

/**
* PacketData class.
* This is used as a container for storing a PSO2Packer, it's a wrapper for a bunch of memcpy calls.
* Also, useful type data could be put here (PSO2 Strings maybe?)
* It's currently broken and crashes the program.
* TODO Fix this class.
*/
class PacketData {
public:
    PacketData(size_t dataSize);
    ~PacketData();
    void appendData(const void* data, size_t length);
    int getSize();
    uint8_t* getData();

private:
    int size;
    int currentPosition;
    uint8_t* dataPtr;
};