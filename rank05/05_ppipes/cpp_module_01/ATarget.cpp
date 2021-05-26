#include "ATarget.hpp"

	const std::string &ATarget::getType(void) const {
		return this->_type;
	}

	ATarget::ATarget(void){}
	ATarget::ATarget(ATarget const &src){}
	ATarget &ATarget::operator=(ATarget const &src){return *this;}
	ATarget::~ATarget(void){}
	ATarget::ATarget(std::string type): _type(type){}
	void ATarget::getHitBySpell(ASpell const &src) const {
		std::cout << this->getType() << " has been " << src.getEffects() << "!\n";
	}

