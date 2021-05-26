#ifndef TARGETGEN
#define TARGETGEN

#include "ATarget.hpp"
#include <vector>

class TargetGenerator {
private:
	TargetGenerator(TargetGenerator const &src);
	TargetGenerator &operator=(TargetGenerator const &src);
	std::vector<ATarget *> book;
public:
	TargetGenerator(void) {}
	~TargetGenerator(void) {
		for(std::vector<ATarget *>::iterator it = book.begin(); it != book.end(); it++)
		{
			delete *it;
		}
		book.clear();
	}


	void learnTargetType(ATarget *spell) {
		if (!spell) return;
		for(std::vector<ATarget *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getType() == spell->getType())
				return;
		}
		book.push_back(spell->clone());
	}


	void forgetTargetType(std::string const &spellname) {
		for(std::vector<ATarget *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getType() == spellname)
			{
				delete *it;
				book.erase(it);
				return;
			}
		}
	}


	ATarget* createTarget (std::string const &spellname) {
		for(std::vector<ATarget *>::iterator it = book.begin(); it != book.end(); it++)
		{
			if((*it)->getType() == spellname)
				return (*it);
		}
		return (NULL);
	}


};

#endif