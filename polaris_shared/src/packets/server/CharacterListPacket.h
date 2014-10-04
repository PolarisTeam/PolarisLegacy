#include "../Packet.h"



class CharacterListPacket : public Packet {

private:
    uint32_t playtimes[12];
};