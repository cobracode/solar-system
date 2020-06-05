#ifndef MATINNIA_DEGMINSEC_H
#define MATINNIA_DEGMINSEC_H

// C++ Libraries
#include <string>

namespace Matinnia {

class DegMinSec {
public:
    // Default Constructor
    DegMinSec();

    // Copy Constructor
    DegMinSec(const DegMinSec& existingDegMinSec);

    // Overloaded Constructors
    explicit DegMinSec(const double value);
    DegMinSec(unsigned int degree, unsigned int minute, unsigned int second, bool isNegative = false);

    // Destructor
    ~DegMinSec();


    // Operators
    DegMinSec& operator= (const DegMinSec& RHS);
    DegMinSec& operator= (const double value);
    DegMinSec operator+ (const DegMinSec& RHS);
    DegMinSec operator+ (const double value);
    DegMinSec operator- (const DegMinSec& RHS);
    DegMinSec operator- (const double value);
    

    // Public Methods
    inline bool            getIsNegative() const    { return isNegative; }
    inline unsigned int    getDegree() const        { return degree; }
    inline unsigned int    getMinute() const        { return minute; }
    inline double          getSecond() const        { return second; }

    inline bool            setNegative(const bool isNegative)   { this->isNegative = isNegative; return true; }
    inline bool            setDegree(const unsigned int degree) { this->degree = degree; return true; }
    inline bool            setMinute(const unsigned int minute) { this->minute = minute; normalizeDegMinSec(); return true; }
    inline bool            setSecond(const double second)       { this->second = second; normalizeDegMinSec(); return true; }

    inline bool            fromDouble(const double value)   { double2DegMinSec(value, *this); return true; }

    inline double               toDouble()      const { return DegMinSec2double(*this); }
    //inline const char* const    toString()      const { return DegMinSec2string(*this); }
    inline void                 toString(char*  const output) const  { DegMinSec2string(*this, output); }
    

    // Static Methods
    static DegMinSec    add(const DegMinSec& LHS, const DegMinSec& RHS);
    static DegMinSec    add(const DegMinSec& LHS, const double RHS);
    static DegMinSec    subtract(const DegMinSec& LHS, const DegMinSec& RHS);
    static DegMinSec    subtract(const DegMinSec& LHS, const double RHS);
    static DegMinSec    subtract(const double LHS, const DegMinSec& RHS);

    static double               DegMinSec2double(const unsigned int degree, const unsigned int minute, const double second, const bool isNegative = false);
    inline static double        DegMinSec2double(const DegMinSec& DMS)  { return DegMinSec2double(DMS.degree, DMS.minute, DMS.second, DMS.isNegative); }
    static const char* const    DegMinSec2string(const DegMinSec& DMS);
    inline static void                 DegMinSec2string(const DegMinSec& DMS, char* const output)   { sprintf(output, "%d°%02u´%09f'", DMS.degree, DMS.minute, DMS.second); }
    static void                 double2DegMinSec(const double value, DegMinSec& output);


private:
    unsigned int    degree;
    unsigned int    minute;
    double          second;
    bool            isNegative;

    // Deep Copy
    void    deepCopy(const DegMinSec& existingDegMinSec);

    // Normalize larger degrees, minutes, and/or seconds to a valid DMS
    inline void    normalizeDegMinSec() { double sum = DegMinSec2double(*this); double2DegMinSec(sum, *this); }

};  // class DegMinSec

};  // namespace Matinnia

#endif  // MATINNIA_DEGMINSEC_H