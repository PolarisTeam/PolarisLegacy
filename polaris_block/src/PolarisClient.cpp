#include "PolarisConnection.h"
#include "PolarisClient.h"
#include "PolarisBlock.h"

std::list<PolarisClient *> clients;

PolarisClient::PolarisClient(PolarisConnection* connection) : theConnection(connection)
{
	PolarisTemp::lastPlayerId++;
    this->player_id = PolarisTemp::lastPlayerId;
    clients.push_back(this);
}

PolarisClient::~PolarisClient()
{
    clients.remove(this);
}

PolarisConnection &PolarisClient::getConnection()
{
    return *this->theConnection;
}
