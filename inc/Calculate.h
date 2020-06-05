#ifndef MATINNIA_CALCULATE_H
#define MATINNIA_CALCULATE_H

// C++ Libraries
#include <map>
using std::map;
using std::multimap;

#include <vector>
using std::vector;

// Project Headers
#include "CalculatedAspect.h"
#include "Logger.h"

namespace Matinnia {

namespace Calculate {

// Convenient Typedefs
typedef map<double, CalculatedAspect>       mapAspectsByOrb;
typedef multimap<size_t, CalculatedAspect>  mapAspectsByBody;

typedef vector<AspectType>                  vecAspectTypes;
typedef vector<CalculatedAspect>            vecAspects;

// I N T E R F A C E
class AspectInserter {
public:
    virtual void operator()(const size_t body1, const size_t body2, const AspectType& aspectType, const double orb) = 0;
};

class AspectByOrbInserter : public AspectInserter {
private:
    mapAspectsByOrb* container;

    AspectByOrbInserter() {}

public:
    AspectByOrbInserter(mapAspectsByOrb& container) :
        container(&container)
    {}

    virtual void operator()(const size_t body1, const size_t body2, const AspectType& aspectType, const double orb) {
        container->insert(container->begin(), std::make_pair(orb, CalculatedAspect(orb, aspectType, body1, body2)));
    }
};

class AspectByBodyInserter : public AspectInserter {
private:
    mapAspectsByBody* container;

    AspectByBodyInserter() {}

public:
    AspectByBodyInserter(mapAspectsByBody& container) :
        container(&container)
    {}

    virtual void operator()(const size_t body1, const size_t body2, const AspectType& aspectType, const double orb) {
        container->insert(container->begin(), std::make_pair(body1, CalculatedAspect(orb, aspectType, body1, body2)));
    }
};

template<typename Iterable>
double* calculateLongitudes(const double julian, const Iterable& bodyIDs) {
    double* longitudes(new double[bodyIDs.size()]);

    if (nullptr != longitudes) {
        // Check if Swiss Ephemeris is initialized or try to initialize it
        if (true == SwissEphemerisInterface::isInitialized || true == initializeSwiss("E:\\Programs\\ZET 9\\Swiss")) {
            size_t count = 0;

            for (auto& body : bodyIDs) {
                longitudes[count++] = getPlanetLongitude(C(int, body), julian);
            }
        }
    }

    return longitudes;
}

inline double normalizedLongitudeDifference(const double val1, const double val2) {
    const double result = fabs(val1 - val2);
    return (result > 180.0) ? 360.0 - result : result;
}

// Calculate aspects between given planet list at given datetime
template<typename Iterable>
void calculateAspects(const vecAspectTypes& aspectTypes, const double julianDate, const Iterable& bodyIDs, AspectInserter& insertAspect) {
    // Calculate longitudes
    double* longitudes(calculateLongitudes(julianDate, bodyIDs));

    if (nullptr != longitudes) {
        // Iterate over "base" bodies
        for (size_t baseIndex = 0; baseIndex < bodyIDs.size(); ++baseIndex) {
            // Iterate over comparison bodies
            for (size_t compareIndex = baseIndex + 1; compareIndex < bodyIDs.size(); ++compareIndex) {
                // Get longitude difference (0 - 180 degrees)
                const double separation = normalizedLongitudeDifference(longitudes[baseIndex], longitudes[compareIndex]);

                // Iterate over aspect types to find match
                for (auto& aspectType : aspectTypes) {
                    // Calculate orb
                    const double orb = fabs(separation - aspectType.getDegree());

                    if (aspectType.getMaxOrb() >= orb) {
                        // Separation is within orb of this aspect; add it
                        insertAspect(bodyIDs[baseIndex], bodyIDs[compareIndex], aspectType, orb);
                    }
                }
            }
        }

        delete[] longitudes;
    }
}



void calculateAspects(const vecAspectTypes& aspectTypes, const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers, AspectInserter& insertAspect);

// Calculate aspects between two datetimes
void calculateAspectsBetween(const vecAspectTypes& aspectTypes, const double julianBase, const double julianCompare,
                             const size_t numberBodies, const size_t* const bodyNumbers, AspectInserter& insertAspect);

// Get longitudes at datetime of all planets/objects in bodyNumbers array
void    getLongitudes               (const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers, double* const longitudes);

// Log aspects at datetime by body
void    logAspectsByBody            (const vecAspectTypes& aspectTypes, const double julian, const size_t numberBodies, const size_t* const bodyNumbers);
void    logAspectsByOrb             (const vecAspectTypes& aspectTypes, const double julian, const size_t numberBodies, const size_t* const bodyNumbers);

// Log longitudes at datetime
void    logLongitudes               (const double julianDate, const size_t numberBodies, const size_t* const bodyNumbers);

// Log aspects from map
template<typename MapContainer>
void logAspectMap(const MapContainer& aspects) {
    char    bodyName1[21];
    char    bodyName2[21];
    char    aspectName[21];

    const Logger& log(Logger::getInstance());

    for (auto& currentAspect : aspects) {
        const CalculatedAspect& aspect(currentAspect.second);

        aspect.getBody1String(bodyName1);
        aspect.getBody2String(bodyName2);
        aspect.getAspectType().getName(aspectName);
        sprintf(Logger::logMessage, "[%.10f]       [%19s]  %-15s  [%-19s]", aspect.getOrb(), bodyName1, aspectName, bodyName2);
        log.writeStatus();
    }
}

};  // namespace Calculate

};  // namespace Matinnia

#endif  // MATINNIA_CALCUALTE_H