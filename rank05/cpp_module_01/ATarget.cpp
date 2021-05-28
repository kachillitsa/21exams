#include <string>
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

    void ATarget::getHitBySpell(ASpell const &as) const {
        std::cout << this->getType() << " has been " << as.getEffects() << "!" << std::endl;
    }
