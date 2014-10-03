#include <locale>
#include "PSO2String.h"

Polaris::Data::PSO2String Polaris::Data::CreatePSO2String(std::u16string sourceString, int subValue, int xorValue) {
    PSO2String theString;

    theString.utf16string = sourceString;

    if(sourceString.empty()) {
        theString.magicValue = (uint32_t) ((subValue) ^ xorValue);
        theString.dataLength = 0;
    } else {
        theString.magicValue = (uint32_t) (((theString.utf16string.size() + 1) + subValue) ^ xorValue);
        if ((theString.utf16string.size() & 1) == 0) {
            // add a padding character
            theString.utf16string.push_back(0);
        }
        theString.dataLength = (uint32_t) ((theString.utf16string.size() + 1) * 2);
    }




    return theString;
}
