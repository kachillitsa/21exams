#ifndef SPELLB
#define SPELLB
#include <iostream>
#include <string>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"

class SpellBook {
private:
    std::vector<ASpell *> _book;
    SpellBook &operator=(SpellBook const &src);
    SpellBook(SpellBook &src);
public:
    SpellBook() {}
    ~SpellBook() {}

    void    learnSpell(ASpell *spell) {
        if (!spell)
            return;
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it) == spell)
                return;
        }
        _book.push_back(spell->clone());
        return;
    }

    void    forgetSpell(std::string const &spell) {
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == spell) {
                delete (*it);
                _book.erase(it);
                return;
            }
        }
        return;
    }
    ASpell* createSpell(std::string const &spell) {
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == spell) {
                return (*it);
            }
        }
        return(NULL);
    }
};

#endif