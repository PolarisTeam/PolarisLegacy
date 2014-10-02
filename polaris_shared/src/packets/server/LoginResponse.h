#include "../Packet.h"

class LoginResponsePacket : public Packet {
public:
    LoginResponsePacket();
    ~LoginResponsePacket();

    PacketData build();
};