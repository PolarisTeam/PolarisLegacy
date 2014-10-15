#pragma once

#include "Poco/Util/ServerApplication.h"

using Poco::Util::ServerApplication;

class PolarisQuery : public ServerApplication
{
public:
    int main(const std::vector<std::string> &args);
};
