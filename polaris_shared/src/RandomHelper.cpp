#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "RandomHelper.h"

namespace Polaris
{
    std::string string_format(const char *fmt, ...)
    {
        char *ret;
        va_list ap;

        va_start(ap, fmt);
        vasprintf(&ret, fmt, ap);
        va_end(ap);

        std::string str(ret);
        free(ret);

        return str;
    }

	uint16_t bswap_uint16(uint16_t a)
	{
		return (uint16_t) (((a & 0xFF) << 8) | ((a & 0xFF00) >> 8));
	}


}


