#include <string>
#include <stdint.h>

namespace Polaris {
    namespace Data {
        struct PSO2String {
            uint32_t magicValue;
            std::u16string utf16string;
            uint32_t dataLength;
        };

        PSO2String CreatePSO2String(std::string sourceString, int subValue, int xorValue);
    }
}
