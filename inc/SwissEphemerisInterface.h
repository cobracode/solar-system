#ifndef MATINNIA_SWISS_EPHEMERIS_INTERFACE_H
#define MATINNIA_SWISS_EPHEMERIS_INTERFACE_H

// C++ Libraries
#include <ctime>

// External Libraries
#include "swephexp.h"       // Swiss Ephemeris

namespace Matinnia {

namespace SwissEphemerisInterface {

    enum COSMIC_BODY {
        SUN = 0,
        MOON,
        MERCURY,
        VENUS,
        MARS,
        JUPITER,
        SATURN,
        URANUS,
        NEPTUNE,
        PLUTO,
        NODE_MEAN,
        NODE_TRUE,
        APOGEE_MEAN,
        APOGEE_OSCULATING,
        EARTH,
        CHIRON,
        PHOLUS,
        CERES,
        PALLAS,
        JUNO,
        VESTA,
        PSYCHE          = 10016,
        SAPPHO          = 10080,
        AMBROSIA        = 10193,
        EROS            = 10433,
        VALENTINE       = 10447,
        CUPIDO          = 10763,
        AMOR            = 11221,
        APHRODITE       = 11388,
        ANTEROS         = 11943,
        ADONIS          = 12101,
        LUST            = 14386,
        COMPASSION      = 18990,
        SWEET           = 21727
    };  // enum COSMIC_BODY


    // Data
    static bool             isInitialized;

    // Methods
    int                     body2Int(const COSMIC_BODY body);
    void                    body2String(const COSMIC_BODY body, char* const output);
    void                    close();
    double                  getPlanetLongitude(const COSMIC_BODY body, const double julianDayUT);
    double                  getPlanetLongitude(const int body, const double julianDayUT);
    bool                    initializeSwiss(const char* const swissDir);
    COSMIC_BODY             int2Body(const unsigned int bodyInt);
    void                    int2BodyString(const int bodyInt, char* const output);
    bool                    string2Body(const string& bodyString, COSMIC_BODY& output);

};  // namespace SwissEphemerisInterface

};  // namespace Matinnia

#endif  // MATINNIA_SWISS_EPHEMERIS_INTERFACE_H