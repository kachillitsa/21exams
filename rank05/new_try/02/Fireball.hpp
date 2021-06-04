#ifndef FIREBALL
#define FIREBALL

#include "ASpell.hpp"

class Fireball: public ASpell {
public:
	Fireball(void): ASpell("Fireball", "burnt to a crisp") {}
	virtual ~Fireball(void) {}
	virtual Fireball *clone(void) const { return (new Fireball); }
};

#endif