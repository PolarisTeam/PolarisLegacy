#include <w32api/xcmc.h>
#include "QueryServerConnection.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(const StreamSocket &socket) : TCPServerConnection(socket) {}

void QueryServerConnection::run() {
    StreamSocket theSock = this->socket();
    std::string message = "Hello!\r\n";
    theSock.sendBytes(message.c_str(), sizeof(message));
    theSock.close();

    return;
}
