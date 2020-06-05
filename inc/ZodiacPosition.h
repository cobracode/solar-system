#ifndef MATINNIA_ZODIACPOSITION_H
#define MATINNIA_ZODIACPOSITION_H

// Project Headers
#include "DegMinSec.h"

namespace Matinnia {

class ZodiacPosition {
public:

    // Data
    enum ZODIAC_SIGN {
        ARIES = 1,
        TAURUS,
        GEMINI,
        CANCER,
        LEO,
        VIRGO,
        LIBRA,
        SCORPIO,
        SAGITTARIUS,
        CAPRICORN,
        AQUARIUS,
        PISCES
    };

    
    // Default Constructor
    ZodiacPosition();

    // Copy Constructor
    ZodiacPosition(const ZodiacPosition& existingZP);

    // Overloaded Constructors
    ZodiacPosition(const double longitude);
    ZodiacPosition(const ZODIAC_SIGN sign);
    ZodiacPosition(const ZODIAC_SIGN sign, const double longitude);
    ZodiacPosition(const ZODIAC_SIGN sign, const DegMinSec& position);

    // Destructor
    ~ZodiacPosition();

    // Public Methods
    inline const DegMinSec&     getPosition() const { return position; }
    inline ZODIAC_SIGN          getSign() const { return sign; }
    inline bool                 setPosition(const DegMinSec& position)  { this->position = position; return true; }
    inline bool                 setSign(const ZODIAC_SIGN sign) { this->sign = sign; return true; }

    // Static Methods
    inline static void          double2ZodiacPosition(const double value, ZodiacPosition& output) { DegMinSec dms; DegMinSec::double2DegMinSec(value, dms); DegMinSec2ZodiacPosition(dms, output); }
    inline static void          double2ZodiacPositionString(const double value, char* const output)  { ZodiacPosition2string(ZodiacPosition(value), output); }

    static void                 DegMinSec2ZodiacPosition(const DegMinSec& DMS, ZodiacPosition& output);

    static ZODIAC_SIGN          int2ZODIAC_SIGN(const unsigned int value);
    static void                 ZodiacPosition2string(const ZodiacPosition& ZP, char* const output);
    static unsigned int         ZODIAC_SIGN2int(const ZODIAC_SIGN sign);
    static void                 ZODIAC_SIGN2string(const ZODIAC_SIGN sign, char* const output);

private:
    DegMinSec       position;
    ZODIAC_SIGN     sign;

    inline void     deepCopy(const ZodiacPosition& RHS)  { if (&RHS != this) { sign = RHS.sign; position = RHS.position; } }
};  // class ZodiacPosition

};  // namespace Matinnia

#endif  // MATINNIA_ZODIACPOSITION_H