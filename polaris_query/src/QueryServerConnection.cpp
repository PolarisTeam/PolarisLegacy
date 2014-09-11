#include "QueryServerConnection.h"
#include "packets/SystemMessagePacket.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(const StreamSocket &socket) : TCPServerConnection(socket) {}

void QueryServerConnection::run() {
    StreamSocket theSock = this->socket();
    SystemMessagePacket systemMsg("This is a message!", 0x3);
    std::vector<uint8_t> data = systemMsg.build();
    theSock.sendBytes(data.data(), (int) data.size());
    //theSock.sendBytes(message.c_str(), message.length());
    theSock.close();

    return;
}
