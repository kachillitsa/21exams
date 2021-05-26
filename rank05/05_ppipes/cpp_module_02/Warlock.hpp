#ifndef WARLOCK
#define WARLOCK

#include <string>
#include <iostream>
#include "ATarget.hpp"
#include "ASpell.hpp"
#include "SpellBook.hpp"
#include <vector>

class Warlock {
private:
	std::string _name;
	std::string _title;
	SpellBook spellbook;
	Warlock(void);
	Warlock(Warlock const &src);
public:
	~Warlock(void) {
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
		spellbook.learnSpell(spell);
	}


	void launchSpell(std::string spellname, ATarget &target) {
		ASpell *spell = spellbook.createSpell(spellname);
		const ATarget *tar = &target;
		if (spell && tar)
			spell->launch(target);
	}


	void forgetSpell(std::string spellname) {
		spellbook.forgetSpell(spellname);
	}


};

#endif