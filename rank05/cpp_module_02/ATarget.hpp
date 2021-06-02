#ifndef ATARGET
#define ATARGET
#include <iostream>
#include <string>
#include "ASpell.hpp"

class ASpell;
class ATarget {
protected:
    std::string _type;
public:
    ATarget &operator=(ATarget const &src) {_type = src._type; return *this;}
    ATarget(ATarget const &src) {*this = src;}
    ATarget() {}
    ATarget(std::string t): _type(t) {}
    virtual ~ATarget() {}
    std::string const &getType() const {return _type;}
    virtual ATarget *clone() const = 0;
    void    getHitBySpell(ASpell const &spell) const;

};

#endif