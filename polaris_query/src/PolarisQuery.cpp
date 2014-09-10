#include <iostream>
#include "Poco/Net/TCPServer.h"
#include "QueryServerFactory.h"
using namespace std;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;

int main() {
    ServerSocket mySocket((Poco::UInt16) 1337);
    QueryServerConnectionFactory* theFactory = new QueryServerConnectionFactory;
    TCPServer theServer(theFactory, mySocket);

    cout << "Listening on port 1337 for connections.";

    theServer.start();

    delete theFactory;

    return 0;
}