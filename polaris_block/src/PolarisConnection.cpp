#include <packets/Packet.h>
#include "packets/server/BlockHelloPacket.h"
#include <string.h>
#include "PolarisConnection.h"
#include "PolarisClient.h"

PolarisConnection::PolarisConnection(const StreamSocket& socket, SocketReactor& reactor):
    socket(socket),
    reactor(reactor),
    bufferPtr(new uint8_t[BUFFER_SIZE]),
    bufferPosition(0)
{
    this->client = new PolarisClient(this);

    reactor.addEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.addEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));

    BlockHelloPacket hello(205);
    PacketData helloData = hello.build(); // TODO Make this cleaner
    this->socket.sendBytes(helloData.getData(), helloData.getSize());
}

PolarisConnection::~PolarisConnection() {
    delete this->client;
    delete[] this->bufferPtr;

    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ReadableNotification>(*this, &PolarisConnection::onReadable));
    reactor.removeEventHandler(socket, NObserver<PolarisConnection, ShutdownNotification>(*this, &PolarisConnection::onShutdown));
}

void PolarisConnection::onShutdown(AutoPtr<ShutdownNotification> const &notification) {
    delete this;
}

void PolarisConnection::onReadable(AutoPtr<ReadableNotification> const &notification) {
    /*
    1. Check if buffer already has data, if so deal with that
    2. No data, new packet, read header
    3. ...things?
    */

    // Fill up the buffer, as much as possible
    int readAmount = socket.receiveBytes(&bufferPtr[bufferPosition], BUFFER_SIZE - bufferPosition);
    bufferPosition += readAmount;

    if (readAmount <= 0) {
        // Connection failed
        delete this;
        return;
    }

    // Enough to process?
    int position = 0;

    while ((position + 4) <= bufferPosition) {
        uint32_t packetSize = *((uint32_t *)&bufferPtr[position]);
        if ((position + packetSize) > bufferPosition) {
            // This packet is unfinished, bail out
            break;
        }

        handlePacket(&bufferPtr[position]);
        position += packetSize;
    }

    // If we handled any packets, we must remove their data from the buffer
    if (position > 0) {
        if (position >= bufferPosition) {
            // End was reached, just empty the thing out.
            bufferPosition = 0;
        } else {
            // Some data remains, move it to the beginning
            memmove(bufferPtr, &bufferPtr[position], bufferPosition - position);
            bufferPosition -= position;
        }
    }
}


void PolarisConnection::handlePacket(uint8_t *packet) {
    PacketHeader *header = (PacketHeader *)packet;

    printf("[Received packet : %d bytes, type %x-%x]\n", header->length, header->command, header->subcommand);
}

