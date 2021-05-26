#ifndef FWOOSH
#define FWOOSH

#include "ASpell.hpp"

class Fwoosh: public ASpell {
public:
	Fwoosh(void): ASpell("Fwoosh", "fwooshed") {}
	virtual ~Fwoosh(void) {}
	virtual Fwoosh *clone(void) const { return (new Fwoosh); }
};

#endif