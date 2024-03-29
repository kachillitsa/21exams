#ifndef WARL
#define WARL
#include <iostream>
#include <string>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"

class Warlock {
private:
    std::string _name;
    std::string _title;
    std::vector<ASpell *> _book;
    Warlock &operator=(Warlock const &src);
    Warlock(Warlock &src);
    Warlock();
public:
    Warlock(std::string n, std::string t): _name(n), _title(t) {
        std::cout << _name << ": This looks like another boring day." << std::endl;
    }
    ~Warlock() {
        std::cout << _name << ": My job here is done!" << std::endl;
    }
    std::string const &getName() const {return _name;}
    std::string const &getTitle() const {return _title;}
    void    setTitle(std::string const &t) {_title = t;}
    void introduce() const {
        std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
    }

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
        void    launchSpell(std::string const &spell, ATarget &tar) {
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == spell) {
                (*it)->launch(tar);
                return;
            }
        }
        return;
    }
};

#endif