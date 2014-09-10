#pragma once

#include "Poco/Net/TCPServerConnectionFactory.h"

class QueryServerConnectionFactory : public Poco::Net::TCPServerConnectionFactory {
public:
    Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket & socket);
};