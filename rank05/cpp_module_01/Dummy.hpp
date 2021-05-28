#ifndef DUMMY
#define DUMMY 

#include "ATarget.hpp"

class Dummy: public ATarget {
public:
    Dummy(): ATarget("Traget Practice Dummy") {};
    virtual ~Dummy() {}
    virtual ATarget *clone() const{
        return (new Dummy(*this));
    }
};
#endif