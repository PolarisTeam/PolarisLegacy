#include <iostream>
#include "PolarisQuery.h"
#include "Poco/Net/TCPServer.h"
#include "QueryServerFactory.h"
using namespace std;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;

int main(int argc, char** argv) {
    PolarisQuery app;
    return app.run(argc, argv);
}

int PolarisQuery::main(const std::vector<std::string> &args) {
    ServerSocket mySocket((Poco::UInt16) 1337);
    QueryServerConnectionFactory* theFactory = new QueryServerConnectionFactory;
    TCPServer theServer(theFactory, mySocket);

    cout << "Listening on port 1337 for connections.";

    theServer.start();

    waitForTerminationRequest();

    delete theFactory;

    return 0;
}