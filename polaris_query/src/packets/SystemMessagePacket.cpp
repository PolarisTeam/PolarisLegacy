#include <malloc.h>
#include <string.h>
#include "SystemMessagePacket.h"

SystemMessagePacket::SystemMessagePacket(std::wstring message, uint32_t messageType){
    this->message = message;
    this->messageType = messageType;
    this->header.length = sizeof(PacketHeader) + sizeof(message) + sizeof(messageType);
    this->header.command = 0x19;
    this->header.subcommand = 0x1;
    this->header.flag1 = 0x4;
}

SystemMessagePacket::~SystemMessagePacket() {
    delete data;
}

PacketHeader SystemMessagePacket::getHeader() {
    return this->header;
}

void *SystemMessagePacket::getData() {
    void* myBuffer = malloc(this->header.length);
    memcpy(myBuffer, &this->header, sizeof(this->header));

    return myBuffer;
}
