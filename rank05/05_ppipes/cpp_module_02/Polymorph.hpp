#ifndef POLYMORPH
#define POLYMORPH

#include "ASpell.hpp"

class Polymorph: public ASpell {
public:
	Polymorph(void): ASpell("Polymorph", "turned into critter") {}
	virtual ~Polymorph(void) {}
	virtual Polymorph *clone(void) const { return (new Polymorph); }
};

#endif