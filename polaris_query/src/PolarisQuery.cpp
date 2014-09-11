#include <iostream>
#include "PolarisQuery.h"
#include "Poco/Net/TCPServer.h"
#include "QueryServerConnection.h"
#include "PolarisShared.h"

using namespace std;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServerConnectionFactoryImpl;

int main(int argc, char** argv) {
    PolarisQuery app;
    return app.run(argc, argv);
}

int PolarisQuery::main(const std::vector<std::string> &args) {
    cout << "Polaris Server Emulator: Ship Query and Block Load balancer." << endl;
    cout << "Compiled against libpolaris_shared verion " << Polaris::GetLibVersion() << " at " << Polaris::GetTimeCompiled() << endl;
    ServerSocket mySocket((Poco::UInt16) 1337);
    TCPServer theServer(new TCPServerConnectionFactoryImpl<QueryServerConnection>, mySocket);

    theServer.start();

    waitForTerminationRequest();

    return 0;
}