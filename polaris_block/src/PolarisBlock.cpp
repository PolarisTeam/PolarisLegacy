#include "PolarisBlock.h"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Thread.h"
#include "PolarisConnection.h"

using Poco::Net::ServerSocket;
using Poco::Net::SocketReactor;
using Poco::Net::SocketAcceptor;
using Poco::Thread;

int main(int argc, char** argv) {
    return PolarisBlockApp().run(argc, argv);
}

int PolarisBlockApp::main(const std::vector<std::string> &args) {
    // Create + Bind socket
    ServerSocket blockSocket(12201); // TODO Config file / Argument / Whatever

    // Make the reactor
    SocketReactor reactor;

    // Assign the Connector
    SocketAcceptor<PolarisConnection> acceptor(blockSocket, reactor);

    Thread thread;
    logger().information("Starting reactor...");
    thread.start(reactor);

    waitForTerminationRequest();

    reactor.stop();
    thread.join();



    return Application::EXIT_OK;
}