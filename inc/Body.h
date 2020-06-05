#ifndef MATINNIA_BODY_H
#define MATINNIA_BODY_H

// C++ Libraries
#include <string>
using std::string;

namespace Matinnia {

class Body {
public:

    struct geocentricOrbitalData {
        double  longitude;
        double  latitude;
        double  distance;
        double  speedLongitude;
        double  speedLatitude;
        double  speedDistance;

        geocentricOrbitalData() :
            longitude(0.0),
            latitude(0.0),
            distance(0.0),
            speedLongitude(0.0),
            speedLatitude(0.0),
            speedDistance(0.0)
        {}
    };  // struct geocentricOrbitalData

    // Default Constructor
    inline Body() : index(0)   {}

    // Copy Constructor
    Body(const Body& RHS)   { deepCopy(RHS); }

    // Overloaded Constructors
    Body(const string& name, const size_t index);
    Body(const string& name, const size_t index, const geocentricOrbitalData& geoData);

    ~Body() {}

private:
    geocentricOrbitalData   geocentricData;
    string                  name;
    size_t                  index;

    void    deepCopy(const Body& RHS);
};

};  // namespace Matinnia

#endif  // MATINNIA_BODY_H