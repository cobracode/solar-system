#ifndef MATINNIA_ASPECTTYPE_H
#define MATINNIA_ASPECTTYPE_H

// C++ Libraries
#include <string>
using std::string;

#include <vector>
using std::vector;


namespace Matinnia {

class AspectType {
public:

    // Default Constructor
    AspectType();

    // Copy Constructor
    AspectType(const AspectType& RHS);

    // Overloaded Constructors
    AspectType(const char* const name, const double degree, const double maxOrb = 1.0);

    // Destructor
    ~AspectType();


    // Public Methods
    inline const char* const    getName() const     { return name.c_str(); }
    inline void                 getName(char* const output) const { strcpy(output, name.c_str()); }
    inline double               getDegree() const   { return degree; }
    inline double               getMaxOrb() const   { return maxOrb; }

    inline bool     setName(const char* const name) { this->name = name; return true; }
    inline bool     setDegree(const double degree)  { this->degree = normalizeDegree(degree); return true; }
    inline bool     setMaxOrb(const double maxOrb)  { this->maxOrb = maxOrb; if (0.0 > maxOrb) { this->maxOrb *= -1.0; } return true; }


    // Static Methods
    static double   normalizeDegree(const double degree);

private:
    double  degree;
    double  maxOrb;
    string  name;

    void    deepCopy(const AspectType& RHS);

};  // class AspectType

};  // namespace Matinnia

#endif  // MATINNIA_ASPECTTYPE_H
