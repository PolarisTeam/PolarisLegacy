#include "../Packet.h"
#include <string>

class LoginResponsePacket : public Packet
{
public:
    LoginResponsePacket(std::u16string loginErr, std::u16string blockName, uint32_t playerId); // TODO: Put all fields in the constructor OR use templates or something to make this less stupid
    ~LoginResponsePacket();

    PacketData build();

private:
	uint32_t playerId;
    std::u16string loginErr;
    std::u16string blockName;
};
