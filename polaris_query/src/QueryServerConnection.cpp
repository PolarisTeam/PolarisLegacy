#include "QueryServerConnection.h"
#include "packets/SystemMessagePacket.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(const StreamSocket &socket) : TCPServerConnection(socket) {}

void QueryServerConnection::run() {
    StreamSocket theSock = this->socket();
    SystemMessagePacket systemMsg("This is a message!", 0x3);
    PacketData data = systemMsg.build();
    theSock.sendBytes(data.getData(), data.getSize());
    theSock.close();

    return;
}
