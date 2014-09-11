#pragma once

#include "Poco/Net/TCPServerConnection.h"

class ShipStatusConnection : public Poco::Net::TCPServerConnection {
public:
    ShipStatusConnection(const Poco::Net::StreamSocket & socket);
    void run();
};