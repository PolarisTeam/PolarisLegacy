#include "ShipBlockConnection.h"
#include "packets/server/ShipBlockPacket.h"

using Poco::Net::StreamSocket

ShipBlockConnection::ShipBlockConnection(const Poco::Net::StreamSocket &socket) : TCPServerConnection(socket) {}

void ShipBlockConnection::run() {
    StreamSocket socket =  this->socket();
    ShipBlockPacket sbp(127, 0, 0, 1, 12201); // Ship 2 block 1
    PacketData blockData = sbp.build();
    socket.sendBytes(blockData.getData(), blockData.getSize());
    socket.close();

    return;

}
