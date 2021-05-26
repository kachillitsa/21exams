#ifndef ATARGET
#define ATARGET

#include <string>
#include <iostream>


class ASpell;

class ATarget {
protected:
	std::string _type;
public:
	const std::string &getType(void) const ;
	ATarget(void);
	ATarget(ATarget const &src);
	ATarget &operator=(ATarget const &src);
	virtual ~ATarget(void);
	virtual ATarget *clone(void) const = 0;
	ATarget(std::string type);
	void getHitBySpell(ASpell const &src) const ;

};


#include "ASpell.hpp"
#endif