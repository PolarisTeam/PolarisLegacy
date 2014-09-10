#include "QueryServerConnection.h"
#include <string>
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(StreamSocket &socket) : TCPServerConnection(socket) {

}


void QueryServerConnection::run() {
    std::string test = "Sup.\r\n";
    StreamSocket theSock = this->socket();
    theSock.sendBytes(test.c_str(), sizeof(test));

    return;
}
