#include <locale>
#include "PSO2String.h"

Polaris::Data::PSO2String Polaris::Data::CreatePSO2String(std::string sourceString, int subValue, int xorValue) {
    PSO2String theString;
    //std::wstring_convert<
    //theString.magicValue = (uint32_t) (((sourceString.size() + 1) + subValue) ^ xorValue);
    //theString.utf16string = convert.;//std::u16string(sourceString);
    //theString.dataLength = (uint32_t) (sizeof(theString.magicValue) + utfstring.size() * sizeof(wchar_t));
    return theString;
}