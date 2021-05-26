#ifndef DUMMY
#define DUMMY

#include "ATarget.hpp"

class Dummy: public ATarget {
public:
	Dummy(void): ATarget("Traget Practice Dummy") {}
	virtual ~Dummy(void) {}
	virtual Dummy *clone(void) const { return (new Dummy); }
};

#endif