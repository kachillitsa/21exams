#ifndef WARL
#define WARL
#include <iostream>
#include <string>

class Warlock {
private:
    std::string _name;
    std::string _title;
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
};

#endif