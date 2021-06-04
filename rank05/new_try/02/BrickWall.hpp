#ifndef WALL
#define WALL

#include "ATarget.hpp"

class BrickWall: public ATarget {
public:
	BrickWall(void): ATarget("Inconspicuous Red-brick Wall") {}
	virtual ~BrickWall(void) {}
	virtual BrickWall *clone(void) const { return (new BrickWall); }
};

#endif