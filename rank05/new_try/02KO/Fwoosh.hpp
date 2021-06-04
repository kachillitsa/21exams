#ifndef FWOO
#define FWOO

#include <string>
#include <iostream>
#include "ASpell.hpp"

class Fwoosh: public ASpell {
public:
	Fwoosh(): ASpell("Fwoosh", "fwooshed") {}
	virtual ~Fwoosh() {}
	virtual ASpell		*clone() const {
		return (new Fwoosh);
	}
};

#endif