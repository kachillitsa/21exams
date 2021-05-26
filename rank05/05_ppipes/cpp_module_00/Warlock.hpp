#include <string>
#include <iostream>

class Warlock {
private:
	std::string _name;
	std::string _title;
	Warlock(void);
	Warlock(Warlock const &src);
	Warlock &operator=(Warlock const &src);
public:
	~Warlock(void) {
		std::cout << this->getName() << ": My job here is done!"
		<< std::endl;
	}


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
};