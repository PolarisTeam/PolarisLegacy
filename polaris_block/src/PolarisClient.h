#pragma once

#include <list>
#include "PolarisConnection.h"

class PolarisClient {
public:
    PolarisClient(PolarisConnection* connection);
    PolarisConnection& getConnection();
    ~PolarisClient();

private:
    PolarisConnection* theConnection;
    std::string sega_id;
    std::u16string current_character_name;
    uint32_t player_id;
};

extern std::list<PolarisClient *> clients;
