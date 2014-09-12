#include "PolarisConnection.h"
#include "PolarisClient.h"

std::list<PolarisClient *> clients;

PolarisClient::PolarisClient(PolarisConnection* connection) : theConnection(connection) {
    clients.push_back(this);
}

PolarisClient::~PolarisClient() {
    clients.remove(this);
}

PolarisConnection &PolarisClient::getConnection() {
    return *this->theConnection;
}
