#include <malloc.h>
#include <cstring>
#include "SystemMessagePacket.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"
#include "Poco/UnicodeConverter.h"

SystemMessagePacket::SystemMessagePacket(std::string message, uint32_t messageType){
    this->message = message;
    this->messageType = messageType;
}

SystemMessagePacket::~SystemMessagePacket() {

}

PacketData SystemMessagePacket::build() {
    // Convert the sting to UTF-16.
    // TODO wstring and whcar_t are 2bytes on windows but 4 bytes on Linux! We should create a PSO2String type at some point to fix this issue.
    std::wstring bigMessage;
    Poco::UnicodeConverter::toUTF16(message, bigMessage);
    PacketHeader header((uint32_t) (sizeof(PacketHeader) + sizeof(uint32_t) + bigMessage.size() * sizeof(wchar_t) + sizeof(uint32_t)), 0x19, 0x01, 0x04, 0x00);
    PacketData data(header.length);
    data.appendData(&header, sizeof(header));
    uint32_t stringMagic = 0; //FIXME
    data.appendData(&stringMagic, sizeof(uint32_t));
    data.appendData(message.data(), message.size() * sizeof(wchar_t));
    data.appendData(&message, sizeof(uint32_t));
    return data;



}
