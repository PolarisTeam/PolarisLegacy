#pragma once

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/AutoPtr.h"
#include "Poco/NObserver.h"

class PolarisClient;

using namespace Poco::Net;
using Poco::AutoPtr;
using Poco::NObserver;

class PolarisConnection {
public:
    PolarisConnection(const StreamSocket& socket, SocketReactor& reactor);
    void onReadable(const AutoPtr<ReadableNotification> &);
    void onShutdown(const AutoPtr<ShutdownNotification> &);
    ~PolarisConnection();

private:
    StreamSocket socket;
    SocketReactor& reactor;
    PolarisClient* client;

    enum { BUFFER_SIZE = 1024 * 16 };
    int bufferPosition; // current end position of the data in the buffer
    uint8_t* bufferPtr;

    void handlePacket(uint8_t *packet);

};
