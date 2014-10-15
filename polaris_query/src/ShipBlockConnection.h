#pragma once

#include "Poco/Net/TCPServerConnection.h"

class ShipBlockConnection : public Poco::Net::TCPServerConnection
{
public:
    ShipBlockConnection(const Poco::Net::StreamSocket & socket);
    void run();
};
