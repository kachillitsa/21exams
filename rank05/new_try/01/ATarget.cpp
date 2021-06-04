#include <string>
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

	void				ATarget::getHitBySpell(ASpell const &spell) const {
		std::cout << this->getType() << " has been " << spell.getEffects() << "!" << std::endl;
	}