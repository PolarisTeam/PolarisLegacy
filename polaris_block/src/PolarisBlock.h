#include "Poco/Util/ServerApplication.h"

using Poco::Util::ServerApplication;
static uint32_t lastPlayerId; //TODO: Do NOT have this as static...

class PolarisBlockApp : public ServerApplication {
public:
    int main(const std::vector<std::string> & args);
};
