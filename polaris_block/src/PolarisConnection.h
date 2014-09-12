#pragma once

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/AutoPtr.h"

class PolarisClient;

using namespace Poco::Net;
using Poco::AutoPtr;

class PolarisConnection {
public:
    PolarisConnection(const StreamSocket& socket, SocketReactor& reactor);
    void onReadable(const AutoPtr<ReadableNotification> &);
    ~PolarisConnection();

private:
    StreamSocket socket;
    SocketReactor& reactor;
    PolarisClient* client;
    std::vector<uint8_t> packet;
    uint8_t* bufferPtr;

};
