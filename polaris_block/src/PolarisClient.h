#pragma once

#include "PolarisConnection.h"

class PolarisClient {
public:
    PolarisClient(PolarisConnection connection);
    ~PolarisClient();

private:
    PolarisConnection theConnection;
};

std::vector<PolarisClient> clients;