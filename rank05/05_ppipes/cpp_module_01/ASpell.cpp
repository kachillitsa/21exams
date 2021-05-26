	
#include "ASpell.hpp"
const std::string &ASpell::getName(void) const {
		return this->_name;
}

const std::string &ASpell::getEffects(void) const {
		return this->_effects;
	}

ASpell::ASpell(void){}
ASpell::ASpell(ASpell const &src){}
ASpell &ASpell::operator=(ASpell const &src){ return *this; }
ASpell::~ASpell(void){}
ASpell::ASpell(std::string name, std::string effects): _name(name), _effects(effects) {}
	
void ASpell::launch(ATarget const &src) const {
		src.getHitBySpell(*this);
}