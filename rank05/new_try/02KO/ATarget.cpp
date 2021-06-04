#include <string>
#include <iostream>
#include "ATarget.hpp"

	void				ATarget::getHitBySpell(ASpell const &spell) const {
		std::cout << this->getType() << " has been " << spell.getEffects() << "!" << std::endl;
	}