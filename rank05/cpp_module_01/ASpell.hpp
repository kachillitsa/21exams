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
    std::string const &getName() const {return _name;}
    std::string const &getEffects() const {return _effects;}
    ASpell() {}
    ASpell(ASpell const &src) : _name(src._name), _effects(src._effects) { *this = src; }
    ASpell &operator=(ASpell const &src){ _name = src._name; _effects = src._effects; return *this; }
    virtual ~ASpell() {}
    virtual ASpell *clone() const = 0;
    ASpell(std::string name, std::string effects): _name(name), _effects(effects) {};
    void launch(ATarget const &at);
};


#include "ATarget.hpp"
#endif