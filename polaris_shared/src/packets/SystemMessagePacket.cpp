#include <malloc.h>
#include <cstring>
#include "SystemMessagePacket.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"
#include "Poco/UnicodeConverter.h"
#include "../data/PSO2String.h"

SystemMessagePacket::SystemMessagePacket(std::string message, uint32_t messageType){
    this->message = message;
    this->messageType = messageType;
}

SystemMessagePacket::~SystemMessagePacket() {

}

PacketData SystemMessagePacket::build() {
    // Convert the sting to a PSO2String.
    Polaris::Data::PSO2String theString = Polaris::Data::CreatePSO2String(message, 0xA2, 0x78F7);
    PacketHeader header((uint32_t) (sizeof(PacketHeader) + sizeof(uint32_t) + theString.utf16string.size() * sizeof(wchar_t) + sizeof(uint32_t)), 0x19, 0x01, 0x04, 0x00);
    PacketData data(header.length);
    data.appendData(&header, sizeof(header));
    data.appendData(&theString, theString.dataLength);
    return data;



}
