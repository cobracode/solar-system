// Own header
#include "CalculatedAspect.h"
using namespace Matinnia;


void CalculatedAspect::deepCopy(const Matinnia::CalculatedAspect &RHS) {
    // Prevent copying yourself
    if (&RHS != this) {
        this->orb           = RHS.orb;
        this->aspectType    = RHS.aspectType;
        this->body1         = RHS.body1;
        this->body2         = RHS.body2;
    }
}