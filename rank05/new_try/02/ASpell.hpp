#ifndef ASP
#define ASP

#include <string>
#include <iostream>
#include "ATarget.hpp"

class ATarget;
class ASpell {
protected:
	std::string _name;
	std::string _effects;
public:
	ASpell() {}
	ASpell(ASpell const &src) {*this = src;}
	ASpell &operator=(ASpell const &src) {
			if (this != &src) {
			_name = src._name;
			_effects = src._effects;
		}
		return (*this);
	}
	ASpell(std::string const &n, std::string const &t): _name(n), _effects(t) {}
	virtual ~ASpell() {}
	std::string const	&getName() const {return _name;}
	std::string const	&getEffects() const {return _effects;}
	virtual ASpell		*clone() const = 0;
	void	launch(ATarget const &tar) const;
};

#endif