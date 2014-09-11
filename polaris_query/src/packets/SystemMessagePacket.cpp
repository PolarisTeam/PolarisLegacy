#include <malloc.h>
#include <cstring>
#include "SystemMessagePacket.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"

SystemMessagePacket::SystemMessagePacket(std::basic_string<char16_t> message, uint32_t messageType){
    this->message = message;
    this->messageType = messageType;
}

SystemMessagePacket::~SystemMessagePacket() {

}

PacketData SystemMessagePacket::build() {

    PacketHeader header((uint32_t) (sizeof(PacketHeader) + sizeof(uint32_t) + message.length() * 2), 0x19, 0x01, 0x04, 0x00);
    PacketData data(header.length);
    data.appendData(&header, sizeof(header));
    data.appendData(&messageType, sizeof(messageType));
    data.appendData(message.data(), message.size() * 2);
    return data;



}
