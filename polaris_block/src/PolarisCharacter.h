#include "data/Character.h"
#include <string>


class PolarisCharacter
{
public:
	PolarisCharacter();
	~PolarisCharacter();

	CharacterJobParameter jobs;
	CharacterLooksParameter looks;
	char16_t name[16];
};