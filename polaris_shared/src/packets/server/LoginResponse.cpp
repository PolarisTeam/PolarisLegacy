#include "LoginResponse.h"
#include "../../data/PSO2String.h"

LoginResponsePacket::LoginResponsePacket(std::u16string loginErr, std::u16string blockName) : loginErr(loginErr), blockName(blockName) {}

LoginResponsePacket::~LoginResponsePacket() {}

PacketData LoginResponsePacket::build() {
    Polaris::Data::PSO2String pso2LoginErr = Polaris::Data::CreatePSO2String(loginErr, 0xB6, 0x8BA4);
    PacketHeader header(sizeof(PacketHeader) + 4 + pso2LoginErr.dataLength + 0xC + 0x40 + 0xB0 + 0xC ,0x11, 0x1, 0x0, 0x0);
    PacketData packetData(header.length);
    packetData.appendData(&header, sizeof(PacketHeader));
    packetData.appendBytes(0, 4); // Unknown uint8 + uint8[3]
    packetData.appendData(&pso2LoginErr.magicValue, 4);
    packetData.appendData(pso2LoginErr.utf16string.data(), pso2LoginErr.dataLength);
    packetData.appendBytes(0, 0xC); // Unknown uint8[0xC]
    packetData.appendData(blockName.data(), blockName.size() * 2);
    if (blockName.size() * 2 < 0x40) { //TODO Verify block name isn't too big
        packetData.appendBytes(0, 0x40 - (blockName.size() * 2)); // Because fixed length
    }
    packetData.appendBytes(0, 0xB0); // Unknown float32[0x2C] ... Likely important!
    packetData.appendBytes(0, 0xC); // Unknown uint8[0xC]


    return packetData;
}
