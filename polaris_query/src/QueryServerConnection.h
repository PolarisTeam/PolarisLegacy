#pragma once

#include "Poco/Net/TCPServerConnection.h"

class QueryServerConnection : public Poco::Net::TCPServerConnection {
public:
    QueryServerConnection(const Poco::Net::StreamSocket & socket);
    void run();
};