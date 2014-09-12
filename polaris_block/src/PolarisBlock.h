#include "Poco/Util/ServerApplication.h"

using Poco::Util::ServerApplication;

class PolarisBlockApp : public ServerApplication {
public:
    int main(const std::vector<std::string> & args);
};
