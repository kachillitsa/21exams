#ifndef FIRE
#define FIRE
#include <iostream>
#include <string>
#include "ATarget.hpp"

class Fireball: public ASpell {
public:
    Fireball(): ASpell("Fireball", "burnt to a crisp") {}
    virtual ~Fireball() {}
    virtual ASpell *clone() const {
        return (new Fireball());
    }
};

#endif