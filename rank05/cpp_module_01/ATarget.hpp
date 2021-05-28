#ifndef ATARGET
#define ATARGET

#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;
class ATarget {
protected:
    std::string _type;

public: 
    ATarget(ATarget const &src) : _type(src._type) { *this = src; }
    ATarget &operator=(ATarget const &src) { _type = src._type; return *this; }
    ATarget() {}
    ATarget(std::string type): _type(type) {};
    virtual ~ATarget() {}
    std::string const &getType() const {return _type;}
    virtual ATarget *clone() const = 0;
    void getHitBySpell(ASpell const &as) const;
};
#endif