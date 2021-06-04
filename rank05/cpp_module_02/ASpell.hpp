#ifndef ASPELL
#define ASPELL
#include <iostream>
#include <string>
#include "ATarget.hpp"

class ATarget;
class ASpell {
protected:
    std::string _name;
    std::string _effects;
public:
    ASpell &operator=(ASpell const &src) {_name = src._name; _effects = src._effects; return *this;}
    ASpell(ASpell const &src) {*this = src;}
    ASpell() {}
    ASpell(std::string n, std::string e): _name(n), _effects(e) {}
    virtual ~ASpell() {}
    std::string const &getName() const {return _name;}
    std::string const &getEffects() const {return _effects;}
    virtual ASpell *clone() const = 0;
    void    launch (ATarget const &tar) const;
};

#endif