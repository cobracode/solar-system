// Own header
#include "ZodiacPosition.h"
using namespace Matinnia;

// C++ Libraries
#include <string>

ZodiacPosition::ZodiacPosition() :
    sign(ARIES)
{}


ZodiacPosition::ZodiacPosition(const Matinnia::ZodiacPosition &existingZP) {
    deepCopy(existingZP);
}


ZodiacPosition::ZodiacPosition(const double longitude) {
    // Convert longitude to sign and position
    double2ZodiacPosition(longitude, *this);
}


ZodiacPosition::ZodiacPosition(const Matinnia::ZodiacPosition::ZODIAC_SIGN sign) :
    sign(sign)
{}


ZodiacPosition::ZodiacPosition(const Matinnia::ZodiacPosition::ZODIAC_SIGN sign, const double longitude) :
    sign(sign)
{
    // If longitude >= 30, ignore it
    if (30.0 > longitude) {
        DegMinSec::double2DegMinSec(longitude, position);
    }
}


ZodiacPosition::ZodiacPosition(const Matinnia::ZodiacPosition::ZODIAC_SIGN sign, const Matinnia::DegMinSec &position) : 
    sign(sign),
    position(position)
{}


ZodiacPosition::~ZodiacPosition()
{}


void ZodiacPosition::DegMinSec2ZodiacPosition(const Matinnia::DegMinSec &DMS, ZodiacPosition& output) {
    output.position = DMS;

    // Correct for degrees out of bounds. Astrological charts only use 0-360.
    unsigned int correctedDegree = DMS.getDegree();

    // If degree > 360, iteratively subtract 360 until it's less than 360
    for (; 360 <= correctedDegree; correctedDegree -= 360) {}

    output.position.setDegree        (correctedDegree);
    output.sign = int2ZODIAC_SIGN(   (correctedDegree / 30) + 1);
    output.position.setDegree        (correctedDegree % 30);
}


ZodiacPosition::ZODIAC_SIGN ZodiacPosition::int2ZODIAC_SIGN(const unsigned int value) {
    ZODIAC_SIGN sign;

    switch (value) {
        case 1:     sign = ARIES;       break;
        case 2:     sign = TAURUS;      break;
        case 3:     sign = GEMINI;      break;
        case 4:     sign = CANCER;      break;
        case 5:     sign = LEO;         break;
        case 6:     sign = VIRGO;       break;
        case 7:     sign = LIBRA;       break;
        case 8:     sign = SCORPIO;     break;
        case 9:     sign = SAGITTARIUS; break;
        case 10:    sign = CAPRICORN;   break;
        case 11:    sign = AQUARIUS;    break;
        case 12:    sign = PISCES;      break;
        default:    sign = ARIES;       break;
    }

    return sign;
}


void ZodiacPosition::ZodiacPosition2string(const ZodiacPosition& ZP, char* const output) {
    char    position[20];
    char    sign[14];

    ZP.position.toString(position);
    ZODIAC_SIGN2string(ZP.sign, sign);
    sprintf(output, "%17s  %-s", position, sign);
}


unsigned int ZodiacPosition::ZODIAC_SIGN2int(const Matinnia::ZodiacPosition::ZODIAC_SIGN sign) {
    unsigned int returnVal = 0;

    switch (sign) {
        case ARIES:         returnVal = 1;      break;
        case TAURUS:        returnVal = 2;      break;
        case GEMINI:        returnVal = 3;      break;
        case CANCER:        returnVal = 4;      break;
        case LEO:           returnVal = 5;      break;
        case VIRGO:         returnVal = 6;      break;
        case LIBRA:         returnVal = 7;      break;
        case SCORPIO:       returnVal = 8;      break;
        case SAGITTARIUS:   returnVal = 9;      break;
        case CAPRICORN:     returnVal = 10;     break;
        case AQUARIUS:      returnVal = 11;     break;
        case PISCES:        returnVal = 12;     break;
        default:            returnVal = 999;    break;
    }

    return returnVal;
}


void ZodiacPosition::ZODIAC_SIGN2string(const ZodiacPosition::ZODIAC_SIGN sign, char* const output) {
    switch (sign) {
        case ARIES:         strcpy(output, "Aries");        break;
        case TAURUS:        strcpy(output, "Taurus");       break;
        case GEMINI:        strcpy(output, "Gemini");       break;
        case CANCER:        strcpy(output, "Cancer");       break;
        case LEO:           strcpy(output, "Leo");          break;
        case VIRGO:         strcpy(output, "Virgo");        break;
        case LIBRA:         strcpy(output, "Libra");        break;
        case SCORPIO:       strcpy(output, "Scorpio");      break;
        case SAGITTARIUS:   strcpy(output, "Sagittarius");  break;
        case CAPRICORN:     strcpy(output, "Capricorn");    break;
        case AQUARIUS:      strcpy(output, "Aquarius");     break;
        case PISCES:        strcpy(output, "Pisces");       break;
        default:            strcpy(output, "UNKNOWN SIGN"); break;
    }
}