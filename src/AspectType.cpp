// Own Header
#include "AspectType.h"
using namespace Matinnia;


AspectType::AspectType() :
    degree(0.0),
    maxOrb(0.0)
{}


AspectType::AspectType(const Matinnia::AspectType &RHS) {
    deepCopy(RHS);
}


AspectType::AspectType(const char* const name, const double degree, const double maxOrb/* = 1.0*/) :
    name(name),
    degree(degree),
    maxOrb(maxOrb)
{
    // Positivize max orb
    if (0.0 > maxOrb) {
        this->maxOrb *= -1.0;
    }

    // Normalize degree in case it's >= 360
    normalizeDegree(this->degree);
}


AspectType::~AspectType() {}


double AspectType::normalizeDegree(const double degree) {
    double result = degree;

    // If degree > 360, bring it to between 0 and 360.
    for (; 360.0 <= result; result -= 360.0) {;}

    // If degree < 0, bring it to between 0 and 360.
    for (; 0.0 >= result; result += 360.0) {;}

    return result;
}


void AspectType::deepCopy(const Matinnia::AspectType &RHS) {
    // Prevent copying yourself
    if (&RHS != this) {
        this->name      = RHS.name;
        this->degree    = RHS.degree;
        this->maxOrb    = RHS.maxOrb;
    }
}