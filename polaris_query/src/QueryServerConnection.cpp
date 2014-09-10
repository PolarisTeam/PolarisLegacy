#include "QueryServerConnection.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(const StreamSocket &socket) : TCPServerConnection(socket) {

}


void QueryServerConnection::run() {
    StreamSocket theSock = this->socket();
    theSock.sendBytes("This is a string.\r\n", sizeof("This is a string.\r\n"));
    theSock.close();

    return;
}
