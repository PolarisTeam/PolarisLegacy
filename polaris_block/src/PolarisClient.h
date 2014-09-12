#pragma once

#include "PolarisConnection.h"

class PolarisClient {
public:
    PolarisClient(PolarisConnection connection);
    ~PolarisClient();
};