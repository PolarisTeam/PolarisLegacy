#include <iostream>
#include "PolarisQuery.h"
#include "Poco/Net/TCPServer.h"
#include "ShipStatusConnection.h"
#include "PolarisShared.h"
#include "ShipBlockConnection.h"

using namespace std;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServerConnectionFactoryImpl;

int main(int argc, char** argv)
{
    PolarisQuery app;
    return app.run(argc, argv);
}

int PolarisQuery::main(const std::vector<std::string> &args)
{
    cout << "Polaris Server Emulator: Ship Query and Block Load balancer." << endl;
    cout << "Compiled against libpolaris_shared verion " << Polaris::GetLibVersion() << " at " << Polaris::GetTimeCompiled() << endl;
    std::vector<TCPServer *> servers;
    for (int i = 0; i < 10; i++)
        servers.push_back(new TCPServer(new TCPServerConnectionFactoryImpl<ShipStatusConnection>, ServerSocket((Poco::UInt16) (12099 + (100 * i)))));

    servers.push_back(new TCPServer(new TCPServerConnectionFactoryImpl<ShipBlockConnection>, ServerSocket((Poco::UInt16) 12200))); // Ship 2 block balancer

    for(auto &i : servers)
        i->start();

    waitForTerminationRequest();

    for (auto &i : servers)
        delete i;

    return 0;
}
