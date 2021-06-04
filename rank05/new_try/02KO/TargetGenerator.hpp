#ifndef TARGEN
#define TARGEN

#include <vector>
#include "ATarget.hpp"

class TargetGenerator {
private:
	std::vector<ATarget *> _book;
	TargetGenerator(TargetGenerator const &src);
	TargetGenerator &operator=(TargetGenerator const &srs);

public:
	TargetGenerator();
	~TargetGenerator() {}

	void	learnTargetType(ATarget *spell) {
		if (!spell) return;
		for (std::vector<ATarget *>::iterator it = _book.begin(); it != _book.end(); it++) {
			if ((*it)->getType() == spell->getType())
				return;
		}
		_book.push_back(spell->clone());
		return;
	}
	void	forgetTargetType(std::string const &spell) {
		for (std::vector<ATarget *>::iterator it= _book.begin(); it != _book.end(); it++) {
			if ((*it)->getType() == spell) {
				delete (*it);
				_book.erase(it);
				return;}
		}
	}
	ATarget *createTarget(std::string const &spell) {
		for (std::vector<ATarget *>::iterator it = _book.begin(); it != _book.end(); it++) {
			if ((*it)->getType() == spell) {
				return (*it);}
		}
		return NULL;
	}
	
};

#endif