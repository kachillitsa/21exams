#ifndef ASPELL
#define ASPELL

#include <string>
#include <iostream>


class ATarget;

class ASpell {
protected:
	std::string _name;
	std::string _effects;
public:
	const std::string &getName(void) const;
	const std::string &getEffects(void) const ;
	ASpell(void);
	ASpell(ASpell const &src);
	ASpell &operator=(ASpell const &src);
	virtual ~ASpell(void);
	virtual ASpell *clone(void) const = 0;
	ASpell(std::string name, std::string effects);
	void launch(ATarget const &src) const ;
};


#include "ATarget.hpp"
#endif