#include "QueryServerFactory.h"

Poco::Net::TCPServerConnection* QueryServerConnectionFactory::createConnection(Poco::Net::StreamSocket const &socket) {
    return NULL;
}
