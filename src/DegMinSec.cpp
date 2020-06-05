// Own header
#include "DegMinSec.h"
using namespace Matinnia;

// C++ Libraries
#include <cmath>
#include <string>


DegMinSec::DegMinSec() :
    isNegative(false),
    degree(0),
    minute(0),
    second(0.0)
{}


DegMinSec::DegMinSec(const Matinnia::DegMinSec &existingDegMinSec) {
    deepCopy(existingDegMinSec);
}


DegMinSec::DegMinSec(const double value) :
    isNegative(false),
    degree(0),
    minute(0),
    second(0.0)
{
    double2DegMinSec(value, *this);   
}


DegMinSec::DegMinSec(unsigned int degree, unsigned int minute, unsigned int second, bool isNegative/* = false*/) {
    this->degree        = degree;
    this->minute        = minute;
    this->second        = second;
    this->isNegative    = isNegative;

    normalizeDegMinSec();
}


DegMinSec::~DegMinSec()
{}


DegMinSec& DegMinSec::operator =(const Matinnia::DegMinSec &RHS) {
    deepCopy(RHS);
    return *this;
}


DegMinSec& DegMinSec::operator =(const double value) {
    double2DegMinSec(value, *this);
    return *this;
}


DegMinSec DegMinSec::operator +(const Matinnia::DegMinSec &RHS) {
    return add(*this, RHS);
}


DegMinSec DegMinSec::operator +(const double value) {
    return add(*this, value);
}


DegMinSec DegMinSec::operator -(const Matinnia::DegMinSec &RHS) {
    return subtract(*this, RHS);
}


DegMinSec DegMinSec::operator -(const double value) {
    return subtract(*this, value);
}


DegMinSec DegMinSec::add(const Matinnia::DegMinSec &LHS, const Matinnia::DegMinSec &RHS) {
    DegMinSec result;
    double2DegMinSec(LHS.toDouble() + RHS.toDouble(), result);
    return result;
}


DegMinSec DegMinSec::add(const Matinnia::DegMinSec &LHS, const double RHS) {
    DegMinSec result;
    double2DegMinSec(LHS.toDouble() + RHS, result);
    return result;
}


DegMinSec DegMinSec::subtract(const Matinnia::DegMinSec &LHS, const Matinnia::DegMinSec &RHS) {
    DegMinSec result;
    double2DegMinSec(LHS.toDouble() - RHS.toDouble(), result);
    return result;
}


DegMinSec DegMinSec::subtract(const Matinnia::DegMinSec &LHS, const double RHS) {
    DegMinSec result;
    double2DegMinSec(LHS.toDouble() - RHS, result);
    return result;
}


DegMinSec DegMinSec::subtract(const double LHS, const Matinnia::DegMinSec &RHS) {
    DegMinSec result;
    double2DegMinSec(LHS - RHS.toDouble(), result);
    return result;
}


double DegMinSec::DegMinSec2double(const unsigned int degree, const unsigned int minute, const double second, const bool isNegative/* = false*/) {
    double returnVal    = static_cast<double>(degree);
    returnVal           += (static_cast<double>(minute) / 60.0);
    returnVal           += (second / 3600.0);

    (true == isNegative) ? returnVal = -returnVal : 1;

    return returnVal;
}


//const char* const DegMinSec::DegMinSec2string(const Matinnia::DegMinSec &DMS) {
//    char*   returnString    = NULL;
//    char    tmp[64];
//
//    sprintf(tmp, "%d°%02u´%09f'", DMS.degree, DMS.minute, DMS.second);
//    returnString = tmp;
//
//    return returnString;
//}


void DegMinSec::double2DegMinSec(const double value, DegMinSec& output) {
    const double correctedValue = (0.0 > value) ? -value : value;

    if (0.0 > value) {
        output.isNegative = true;
    }

    output.degree = static_cast<unsigned int>(floor(correctedValue));
    double valueSubDegree = correctedValue - static_cast<double>(output.degree);
    double minuteValue = valueSubDegree * 60.0;

    output.minute = static_cast<unsigned int>(floor(minuteValue));
    double valueSubMinute = minuteValue - static_cast<double>(output.minute);
    output.second = valueSubMinute * 60.0;
}


void DegMinSec::deepCopy(const Matinnia::DegMinSec &existingDegMinSec) {
    // Prevent copying yourself
    if (&existingDegMinSec != this) {
        this->isNegative    = existingDegMinSec.isNegative;
        this->degree        = existingDegMinSec.degree;
        this->minute        = existingDegMinSec.minute;
        this->second        = existingDegMinSec.second;
    }
}