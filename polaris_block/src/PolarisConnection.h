#pragma once

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/AutoPtr.h"
#include "Poco/NObserver.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CryptoTransform.h"

class PolarisClient;
class PacketData;

using namespace Poco::Net;
using namespace Poco::Crypto;
using Poco::AutoPtr;
using Poco::NObserver;

class PolarisConnection {
public:
    PolarisConnection(const StreamSocket& socket, SocketReactor& reactor);
    void onReadable(const AutoPtr<ReadableNotification> &);
    void onShutdown(const AutoPtr<ShutdownNotification> &);
    ~PolarisConnection();

    void sendPacket(PacketData &data);

private:
    StreamSocket socket;
    SocketReactor& reactor;
    PolarisClient* client;

    Poco::AutoPtr<Cipher> cipher;
    CryptoTransform *outputTransform, *inputTransform;

    enum { BUFFER_SIZE = 1024 * 16 };

    int packetCount = 0;
    std::time_t connTime;

    int bufferPosition; // current end position of the data in the buffer
    uint8_t* bufferPtr;

    void handlePacket(uint8_t *packet);

    void handleKeyExchange(uint8_t *packet);

    void playbackPackets(std::string folder, int startPkt, int endPkt);

};
