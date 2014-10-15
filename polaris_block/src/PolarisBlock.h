#include "Poco/Util/ServerApplication.h"
#include "PolarisCharacter.h"

using Poco::Util::ServerApplication;

/*
* This is a temporary namespace for features that are being worked on, EVERYTHING HERE will go away someday
* FIXME: Remove this
*/
namespace PolarisTemp
{
	static uint32_t lastPlayerId;
	static PolarisCharacter lastCharacter;
}

class PolarisBlockApp : public ServerApplication
{
public:
    int main(const std::vector<std::string> &args);
};
