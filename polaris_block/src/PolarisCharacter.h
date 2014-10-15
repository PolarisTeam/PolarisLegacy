#include "data/Character.h"
#include <string>


class PolarisCharacter
{
public:
	PolarisCharacter();
	~PolarisCharacter();

	CharacterJobParameter jobs;
	CharacterLooksParameter looks;
	std::u16string name;
};