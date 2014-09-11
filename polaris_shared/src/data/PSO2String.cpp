#include <string>
#include "PSO2String.h"
#include "Poco/UnicodeConverter.h"

Polaris::Data::PSO2String Polaris::Data::CreatePSO2String(std::string sourceString, int subValue, int xorValue) {
    PSO2String theString;
    theString.magicValue = ((sourceString.size() + 1) + subValue) ^ xorValue;
    std::wstring utfstring;
    Poco::UnicodeConverter::toUTF16(sourceString, utfstring);
    theString.utf16string = utfstring;
    theString.dataLength = sizeof(theString.magicValue) + utfstring.size() * sizeof(wchar_t);
    return utfstring;
}