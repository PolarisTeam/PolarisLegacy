#include "QueryServerConnection.h"
#include "packets/SystemMessagePacket.h"
#include "packets/ShipListPacket.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

QueryServerConnection::QueryServerConnection(const StreamSocket &socket) : TCPServerConnection(socket) {}

void QueryServerConnection::run() {
    StreamSocket theSock = this->socket();

    //SystemMessagePacket systemMsg("This is a cool message, bro!", 0x3);
    //PacketData data = systemMsg.build();

    ShipListPacket shipList;
    shipList.addShip(1000, u"Ship01", 210,189,208,1, 1, 6, 0x8D677);
    shipList.addShip(2000, u"Ship02", 210,189,208,16, 1, 7, 0x98E0C);
    shipList.addShip(3000, u"Ship03", 210,189,208,31, 1, 8, 0xB13B6);
    shipList.addShip(4000, u"Ship04", 210,189,208,46, 1, 9, 0xB1389);
    shipList.addShip(5000, u"Ship05", 210,189,208,61, 1, 10, 0xB13A2);
    shipList.addShip(6000, u"Ship06", 210,189,208,76, 1, 1, 0xADA99);
    shipList.addShip(7000, u"Ship07", 210,189,208,91, 1, 2, 0xB13B7);
    shipList.addShip(8000, u"Ship08", 210,189,208,106, 1, 3, 0xB13B9);
    shipList.addShip(9000, u"Ship09", 210,189,208,121, 1, 4, 0xB13B8);
    shipList.addShip(10000, u"Ship10", 210,189,208,136, 1, 5, 0xA209C);

    PacketData data = shipList.build();

    theSock.sendBytes(data.getData(), data.getSize());
    theSock.close();

    return;
}
