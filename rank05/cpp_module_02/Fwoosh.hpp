#ifndef FWOO
#define FWOO
#include <iostream>
#include <string>
#include "ATarget.hpp"

class Fwoosh: public ASpell {
public:
    Fwoosh(): ASpell("Fwoosh", "fwooshed") {}
    virtual ~Fwoosh() {}
    virtual ASpell *clone() const {
        return (new Fwoosh());
    }
};

#endif