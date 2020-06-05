#ifndef MATINNIA_CALCULATEDASPECT_H
#define MATINNIA_CALCULATEDASPECT_H

// C++ Libraries
#include <string>
using std::string;

#include <utility>
using std::pair;

// Project Headers
#include "AspectType.h"
#include "MiscDefinitions.h"
#include "SwissEphemerisInterface.h"
using namespace Matinnia::SwissEphemerisInterface;

namespace Matinnia {

class CalculatedAspect {
public:
    // Default Constructor
    inline CalculatedAspect() : body1(0), body2(0), orb(0.0) {}

    // Overloaded Constructors
    inline CalculatedAspect(const double orb, const AspectType& aspectType, const size_t body1, const size_t body2) :
        aspectType(aspectType),
        body1(body1),
        body2(body2),
        orb(orb)
    {}

    // Destructor
    inline ~CalculatedAspect() {}


    // Public Methods
    inline double               getOrb() const          { return orb; }
    inline const AspectType&    getAspectType() const   { return aspectType; }
    inline size_t               getBody1() const        { return body1; }
    inline size_t               getBody2() const        { return body2; }
    inline void                 getBody1String(char* const output) const    { int2BodyString(C(int, body1), output); }
    inline void                 getBody2String(char* const output) const    { int2BodyString(C(int, body2), output); }

    inline bool setOrb(const double orb)                            { this->orb = orb; /*normalizeOrb(orb);*/ return true; }
    inline bool setAspectType(const AspectType& aspectType)         { if (0 < strlen(aspectType.getName())) { this->aspectType = aspectType; return true; } else { return false; }}

    
    // Static Methods
    inline static double   normalizeOrb(const double orb)   { double result = orb; for (; 360.0 <= result; result -= 360.0) {;} for (; -360.0 >= result; result += 360.0) {;} return result; }


private:
    AspectType  aspectType;
    size_t      body1;
    size_t      body2;
    double      orb;

    void        deepCopy(const CalculatedAspect& RHS);
};  // class CalculatedAspect

};  // namespace Matinnia

#endif  // MATINNIA_CALCULATEDASPECT_H