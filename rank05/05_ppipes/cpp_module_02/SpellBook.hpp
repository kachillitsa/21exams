#ifndef SPELLBOOK
#define SPELLBOOK

#include "ASpell.hpp"
#include <vector>

class SpellBook {
private:
	SpellBook(SpellBook const &src);
	SpellBook &operator=(SpellBook const &src);
	std::vector<ASpell *> book;
public:
	SpellBook(void){}
	~SpellBook(void) {
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			delete *it;
		}
		book.clear();
	}


	void learnSpell(ASpell *spell) {
		if (!spell) return;
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getName() == spell->getName())
				return;
		}
		book.push_back(spell->clone());
	}


	void forgetSpell(std::string const &spellname) {
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getName() == spellname)
			{
				delete *it;
				book.erase(it);
				return;
			}
		}
	}


	ASpell* createSpell(std::string const &spellname) {
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getName() == spellname)
				return (*it);
		}
		return (NULL);
	}


};

#endif