#include <string>
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

	void	ASpell::launch(ATarget const &tar) const {
		tar.getHitBySpell(*this);
	}