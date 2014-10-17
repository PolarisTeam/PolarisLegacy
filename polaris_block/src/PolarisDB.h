#include "Poco/Data/Common.h"

using namespace Poco::Data;
class PolarisDB
{
private:
	PolarisDB();
	// Prevent copies of this
	PolarisDB(PolarisDB const& copy);
	PolarisDB& operator=(PolarisDB const& copy);
	Session dbSession;
public:
	static PolarisDB getInstance();
};
