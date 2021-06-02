#include "ASpell.hpp"

    void    ASpell::launch (ATarget const &tar) const {
        tar.getHitBySpell(*this);
    }