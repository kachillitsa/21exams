#include <string>
#include <iostream>
#include "ATarget.hpp"
#include "ASpell.hpp"

    void ASpell::launch(ATarget const &at) {
        at.getHitBySpell(*this);
    }