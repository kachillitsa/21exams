#ifndef DUM
#define DUM

#include <string>
#include <iostream>
#include "ATarget.hpp"

class Dummy: public ATarget {
public:
	Dummy(): ATarget("Target Practice Dummy") {}
	virtual ~Dummy() {}
	virtual ATarget		*clone() const {
		return (new Dummy);
	}
};

#endif