#ifndef POLY
#define POLY
#include <iostream>
#include <string>
#include "ATarget.hpp"

class Polymorph: public ASpell {
public:
    Polymorph(): ASpell("Polymorph", "turned into a critter") {}
    virtual ~Polymorph() {}
    virtual ASpell *clone() const {
        return (new Polymorph());
    }
};

#endif