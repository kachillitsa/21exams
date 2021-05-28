#ifndef WARLOCK
#define WARLOCK

#include <string>
#include <iostream>
#include "ATarget.hpp"
#include "ASpell.hpp"
#include <vector>

class Warlock {
private:
	std::string _name;
	std::string _title;
	std::vector<ASpell *> book;
	Warlock(void);
	Warlock(Warlock const &src);
public:
	~Warlock(void) {
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			delete *it;
		}
		book.clear();
		std::cout << this->getName() << ": My job here is done!"
		<< std::endl;
	}
	Warlock &operator=(Warlock const &src);
	const std::string &getName(void) const {
		return this->_name;
	}
	const std::string &getTitle(void) const {
		return this->_title;
	}
	void setTitle(const std::string &src) {
		this->_title = src;
	}
	Warlock(std::string name, std::string title):
	_name(name), _title(title) {
		std::cout << this->getName() << ": This looks like another boring day."
		<< std::endl;
	}
	void introduce(void) const {
		std::cout << this->getName() << ": I am " << this->getName() << ", "
		<< this->getTitle() << "!" << std::endl;
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

	void launchSpell(std::string spellname, ATarget &target) {
		for(std::vector<ASpell *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getName() == spellname)
			{
				(*it)->launch(target);
				return;
			}
		}
	}

	void forgetSpell(std::string spellname) {
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


};

#endif