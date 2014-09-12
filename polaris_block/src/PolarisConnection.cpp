#include <packets/Packet.h>
#include "PolarisConnection.h"
#include "PolarisClient.h"

PolarisConnection::PolarisConnection(const StreamSocket& socket, SocketReactor& reactor):
    socket(socket),
    reactor(reactor),
    bufferPtr(new uint8_t[1000])
{
    this->client = new PolarisClient(this);
}

PolarisConnection::~PolarisConnection() {
    delete this->client;
    delete[] this->bufferPtr;
}

void PolarisConnection::onReadable(AutoPtr<ReadableNotification> const &notification) {
    /*
    1. Check if buffer already has data, if so deal with that
    2. No data, new packet, read header
    3. ...things?
    */


    this->socket;
}
