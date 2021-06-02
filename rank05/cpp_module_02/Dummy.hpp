#ifndef DUMMY
#define DUMMY
#include <iostream>
#include <string>
#include "ATarget.hpp"

class Dummy: public ATarget {
public:
    Dummy(): ATarget("Target Practice Dummy") {}
    virtual ~Dummy() {}
    virtual ATarget *clone() const {
        return (new Dummy());
    }
};

#endif