#ifndef WARLOCK
#define WARLOCK

#include <string>
#include <iostream>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;
	SpellBook _book;
	Warlock();
	Warlock(Warlock const &src);
	Warlock &operator=(Warlock const &srs);

public:
	Warlock(std::string const &n, std::string const &t): _name(n), _title(t) {std::cout << this->getName() << ": This looks like another boring day."<< std::endl;}
	~Warlock() {std::cout << this->getName() << ": My job here is done!"<< std::endl;}
	std::string const &getName() const {return _name;}
	std::string const &getTitle() const {return _title;}
	void	setTitle(std::string const &s) {_title = s;}
	void	introduce(void) const {std::cout << this->getName() << ": I am " << this->getName() << ", "<< this->getTitle() << "!" << std::endl;}
	void	learnSpell(ASpell *spell) {
		_book.learnSpell(spell);
	}
	void	forgetSpell(std::string const &spell) {
			_book.forgetSpell(spell);
	}
	void	launchSpell(std::string const &spell, ATarget const &tar) {
		if (_book.createSpell(spell))
			tar.getHitBySpell(*(_book.createSpell(spell)));
	}
};

#endif