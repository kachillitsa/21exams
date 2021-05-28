#ifndef WARLOCK
#define WARLOCK

#include <string>
#include <iostream>
#include <vector>
#include "ATarget.hpp"
#include "ASpell.hpp"

class Warlock {
private:
    std::string _name;
    std::string _title;
    std::vector<ASpell *> _book;
    Warlock();
    Warlock(Warlock &src);
    Warlock &operator=(Warlock const &src);
public:

    Warlock(std::string name, std::string title): _name(name), _title(title) {
        std::cout << _name << ": This looks like another boring day." << std::endl;}
    ~Warlock() { std::cout << _name << ": My job here is done!" << std::endl; }
    std::string const &getName() const {return _name;}
    std::string const &getTitle() const {return _title;}
    void    setTitle(std::string const &s) {_title = s; return;}
    void introduce() const {
        std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
    }


    void learnSpell(ASpell *asp) {
        if (!asp) return;
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == asp->getName())
                    return;
        }
        _book.push_back(asp->clone());
    }

    void forgetSpell(std::string const &sp) {
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == sp) {
                delete *it;
                _book.erase(it);
                return;
            }
        }
    }
    void launchSpell(std::string sp, ATarget const &at) {
        
        for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
            if ((*it)->getName() == sp) {
                (*it)->launch(at);
                return;
            }
        }
    }
};

#endif