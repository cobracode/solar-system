#ifndef MATINNIA_ASTROLOGY_TOOL_H
#define MATINNIA_ASTROLOGY_TOOL_H

// C++
#include <ostream>
using std::ostream;
using std::endl;
#include <vector>
using std::vector;

// Project
#include "AspectType.h"

namespace Matinnia {

// INTERFACE
template<typename Aspects>
class ActOnAspects {
public:
    virtual void operator()(Aspects& aspects) = 0;
};

template<typename Aspects>
class StreamAspects : public ActOnAspects<Aspects> {
private:
    ostream* stream;

    StreamAspects() {}

public:
    StreamAspects(ostream& stream) :
        stream(&stream)
    {}

    virtual void operator()(Aspects& aspects) {
        for (auto& aspect : aspects) {
            const CalculatedAspect& calculatedAspect(aspect.second);
            const AspectType& aspectType(calculatedAspect.getAspectType());

            // Example:   Sun square Moon 3.48 deg          
            char body1[30] = {0};
            char body2[30] = {0};
            calculatedAspect.getBody1String(body1);
            calculatedAspect.getBody2String(body2);            

            *stream << body1 << " " << aspectType.getName() << " " << body2 << "    "
                    << calculatedAspect.getOrb() << endl;
        }
    }
};

template<typename Aspects>
class LogAspects : public ActOnAspects<Aspects> {
public:
    virtual void operator()(Aspects& aspects) {

    }
};

//void actOnAspects(aspects, action)

class AstrologyTool {
public:
    typedef vector<AspectType>  AspectTypes;
    typedef vector<size_t>      BodyIDs;

    void logCurrentAspects() const;
    void printCurrentAspects();
    void streamCurrentAspects(ostream& stream) const;

    template<typename Aspects>
    void aspectAction(Aspects& aspects, ActOnAspects<Aspects>& action);

private:

    static AspectTypes  loadAspectTypes();
    static BodyIDs      loadBodyIDs();

    // Data
    static AspectTypes  aspectTypes;
    static BodyIDs      bodyIDs;
};  // class AstrologyTool


// TEMPLATIZED METHODS
template<typename Aspects>
void AstrologyTool::aspectAction(Aspects& aspects, ActOnAspects<Aspects>& action) {
    action(aspects);
}

}   // namespace Matinnia

#endif  // MATINNIA_ASTROLOGY_TOOL_H