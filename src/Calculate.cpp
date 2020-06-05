// Own header
#include "Calculate.h"

// Project Headers
#include "SwissEphemerisInterface.h"
#include "ZodiacPosition.h"
using namespace Matinnia;


void Calculate::calculateAspects(const vecAspectTypes& aspectTypes, const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers, AspectInserter& insertAspect) {
    // Calculate longitudes
    double* longitudes(new double[numberBodies]);

    if (NULL != longitudes) {
        getLongitudes(julianDate, numberBodies, bodyNumbers, longitudes);

        double orb, separation;
        size_t index, compareIndex;

        // Iterate over all bodies to get their aspects between each other
        for (index = 0; numberBodies > index; ++index) {
            for (compareIndex = index + 1; numberBodies > compareIndex; ++compareIndex) {
                // Get the raw longitude separation
                separation = fabs(longitudes[index] - longitudes[compareIndex]);

                // Normalize to between 0-180 degrees
                (180.0 < separation) ? separation = 360.0 - separation : 1;

                // Iterate over aspect types to check if any match
                for (auto& aspectType : aspectTypes) {
                    // Get orb between separation and aspect angle
                    orb = fabs(aspectType.getDegree() - separation);

                    // If orb is within range, add it
                    if (aspectType.getMaxOrb() >= orb) {
                        insertAspect(bodyNumbers[index], bodyNumbers[compareIndex], aspectType, orb);
                        break;
                    }
                }
            }
        }

        delete[] longitudes;
    }
}

void Calculate::calculateAspectsBetween(const vecAspectTypes& aspectTypes, const double julianBase, const double julianCompare,
                                        const size_t numberBodies, const size_t* const bodyNumbers, AspectInserter& insertAspect) {
    // Allocate memory for n=numberBodies longitudes to compare
    double* longitudesBase(new double[numberBodies]);

    if (NULL != longitudesBase) {
        double* longitudesCompare(new double[numberBodies]);

        if (NULL != longitudesCompare) {
            // Calculate longitudes
            getLongitudes(julianBase, numberBodies, bodyNumbers, longitudesBase);
            getLongitudes(julianCompare, numberBodies, bodyNumbers, longitudesCompare);

            double orb, separation;
            size_t indexBase, indexCompare;

            // Iterate over both the base and comparison
            // to check for and save aspects found
            for (indexBase = 0; numberBodies > indexBase; ++indexBase) {
                for (indexCompare = 0; numberBodies > indexCompare; ++indexCompare) {
                    // Raw difference in longitudes
                    separation = fabs(longitudesBase[indexBase] - longitudesCompare[indexCompare]);

                    // Normalize separation to between 0 - 180 degrees (orb)
                    (180.0 < separation) ? separation = 360.0 - separation : 1;

                    // Iterate over the aspect types to see if this difference is within orb of them
                    for (auto& aspect : aspectTypes) {
                        orb = fabs(aspect.getDegree() - separation);

                        // If within orb of this aspect, save it
                        if (aspect.getMaxOrb() >= orb) {
                            // Abstract what changes. This changes.
                            insertAspect(bodyNumbers[indexBase], bodyNumbers[indexCompare], aspect, orb);
                            break;
                        }
                    }
                }
            }

            delete[] longitudesCompare;
        }

        delete[] longitudesBase;
    }
}


void Calculate::getLongitudes(const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers, double* const longitudes) {
    // Check if Swiss Ephemeris is initialized or try to initialize it
    if (true == SwissEphemerisInterface::isInitialized || true == initializeSwiss("E:\\Programs\\ZET 9\\Swiss")) {
        for (size_t index(0); numberBodies > index; ++index) {
            longitudes[index] = getPlanetLongitude(C(int, bodyNumbers[index]), julianDate);
        }
    }
}


void Calculate::logLongitudes(const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers) {
    // Get longitudes
    double* longitudes(new double[numberBodies]);

    if (NULL != longitudes) {
        getLongitudes(julianDate, numberBodies, bodyNumbers, longitudes);

        char    tmp1[40];
        char    tmp2[40];

        const Logger& log(Logger::getInstance());

        for (size_t index(0); numberBodies > index; ++index) {
            int2BodyString(C(int, bodyNumbers[index]), tmp1);
            ZodiacPosition::double2ZodiacPositionString(longitudes[index], tmp2);

            sprintf(Logger::logMessage, "%19s   %s", tmp1, tmp2);
            log.writeStatus();
        }

        delete[] longitudes;
    }
}


void Calculate::logAspectsByBody(const vecAspectTypes& aspectTypes, const double julian, const size_t numberBodies, const size_t* const bodyNumbers) {
    mapAspectsByBody aspects;
    AspectByBodyInserter inserter(aspects);
    calculateAspects(aspectTypes, julian, numberBodies, bodyNumbers, inserter);
    logAspectMap(aspects);
}


void Calculate::logAspectsByOrb(const vecAspectTypes& aspectTypes, const double julian, const size_t numberBodies, const size_t* const bodyNumbers) {
    mapAspectsByOrb aspects;
    AspectByOrbInserter inserter(aspects);
    calculateAspects(aspectTypes, julian, numberBodies, bodyNumbers, inserter);
    logAspectMap(aspects);
}