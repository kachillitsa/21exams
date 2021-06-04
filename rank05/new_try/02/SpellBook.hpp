#ifndef SPELLB
#define SPELLB

#include <string>
#include <iostream>
#include <vector>
#include "ASpell.hpp"

class SpellBook {
private:
	std::vector<ASpell *> _book;
	SpellBook(SpellBook const &src);
	SpellBook &operator=(SpellBook const &srs);

public:
	SpellBook() {}
	~SpellBook() {}
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
	ASpell* createSpell(std::string const &spell) {
		for (std::vector<ASpell *>::iterator it = _book.begin(); it != _book.end(); it++) {
			if ((*it)->getName() == spell) {
				return (*it);}
		}
		return NULL;
	}
};

#endif