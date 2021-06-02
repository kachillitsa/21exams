#ifndef TARGEN
#define TARGEN
#include <iostream>
#include <string>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"

class TargetGenerator {
private:
    std::vector<ATarget *> _book;
    TargetGenerator &operator=(TargetGenerator const &src);
    TargetGenerator(TargetGenerator &src);
public:
    TargetGenerator() {}
    ~TargetGenerator() {}

    void    learnTargetType(ATarget *spell) {
        if (!spell)
            return;
        for (std::vector<ATarget *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it) == spell)
                return;
        }
        _book.push_back(spell->clone());
        return;
    }

    void    forgetTargetType(std::string const &spell) {
        for (std::vector<ATarget *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getType() == spell) {
                delete (*it);
                _book.erase(it);
                return;
            }
        }
        return;
    }
    ATarget* createTarget(std::string const &spell) {
        for (std::vector<ATarget *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getType() == spell) {
                return (*it);
            }
        }
        return(NULL);
    }
};

#endif