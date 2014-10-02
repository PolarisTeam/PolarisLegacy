#include "../Packet.h"
#include <string>

class LoginResponsePacket : public Packet {
public:
    LoginResponsePacket(std::u16string loginErr, std::u16string blockName); //TODO: Put all fields in the constructor OR use templates or something to make this less stupid
    ~LoginResponsePacket();

    PacketData build();

private:
    std::u16string loginErr;
    std::u16string blockName;
};