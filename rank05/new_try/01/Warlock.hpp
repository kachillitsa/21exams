#ifndef WARLOCK
#define WARLOCK

#include <string>
#include <iostream>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;
	std::vector<ASpell *> _book;
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
		if (!spell) return;
		for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
			if ((*it)->getName() == spell->getName())
				return;
		}
		_book.push_back(spell->clone());
		return;
	}
	void	forgetSpell(std::string const &spell) {
		for (std::vector<ASpell *>::iterator it= _book.begin(); it != _book.end(); it++) {
			if ((*it)->getName() == spell) {
				delete (*it);
				_book.erase(it);
				return;}
		}
	}
	void	launchSpell(std::string const &spell, ATarget const &tar) {
		for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
			if ((*it)->getName() == spell) {
				(*it)->launch(tar);
				return;}
		}
	}
};

#endif