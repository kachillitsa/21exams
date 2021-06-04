#ifndef ATAR
#define ATAR

#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;
class ATarget {
protected:
	std::string _type;
public:
	ATarget() {}
	ATarget(ATarget const &src) {*this = src;}
	ATarget &operator=(ATarget const &src) {
			if (this != &src) {
			_type = src._type;
		}
		return (*this);
	}
	ATarget(std::string const &n): _type(n) {}
	virtual ~ATarget() {}
	std::string const	&getType() const {return _type;}
	virtual ATarget		*clone() const = 0;
	void				getHitBySpell(ASpell const &spell) const;
};

#endif