// Own Header
#include "AstrologyTool.h"

// C++
#include <iostream>
using std::cout;

// Project
#include "Calculate.h"
#include "MyDate.h"

namespace Matinnia {

AstrologyTool::AspectTypes  AstrologyTool::aspectTypes(AstrologyTool::loadAspectTypes());
AstrologyTool::BodyIDs      AstrologyTool::bodyIDs(AstrologyTool::loadBodyIDs());

AstrologyTool::AspectTypes AstrologyTool::loadAspectTypes() {
    AspectTypes types;

    types.push_back(AspectType("conjunct",        0.0,                5.0));
    types.push_back(AspectType("semisextile",     30.0,               1.0));
    types.push_back(AspectType("eleven",          32.72727272727273,  0.5));
    types.push_back(AspectType("semisquare",      45.0,               2.0));
    types.push_back(AspectType("novile",          40.0,               1.0));
    types.push_back(AspectType("septile",         51.42857142857143,  0.5));
    types.push_back(AspectType("sextile",         60.0,               4.0));
    types.push_back(AspectType("quintile",        72.0,               1.0));
    types.push_back(AspectType("binovile",        80.0,               1.0));
    types.push_back(AspectType("square",          90.0,               4.0));
    types.push_back(AspectType("biseptile",       102.8571428571429,  0.5));
    types.push_back(AspectType("trine",           120.0,              4.0));
    types.push_back(AspectType("sesqisquare",     135.0,              2.0));
    types.push_back(AspectType("biquintile",      144.0,              1.0));
    types.push_back(AspectType("quincunx",        150.0,              1.0));
    types.push_back(AspectType("triseptile",      154.2857142857143,  0.5));
    types.push_back(AspectType("quatronovile",    160.0,              1.0));
    types.push_back(AspectType("opposition",      180.0,              5.0));

    return types;
}

AstrologyTool::BodyIDs AstrologyTool::loadBodyIDs() {
    BodyIDs IDs;

    IDs.push_back(0);
    IDs.push_back(1);
    IDs.push_back(2);
    IDs.push_back(3);
    IDs.push_back(4);
    IDs.push_back(5);
    IDs.push_back(6);
    IDs.push_back(7);
    IDs.push_back(8);
    IDs.push_back(9);   // 10

    IDs.push_back(11);
    IDs.push_back(15);
    IDs.push_back(16);
    IDs.push_back(17);
    IDs.push_back(18);
    IDs.push_back(19);
    IDs.push_back(20);  // 7

    IDs.push_back(10015);
    IDs.push_back(10016);
    IDs.push_back(10019);
    IDs.push_back(10023);
    IDs.push_back(10030);
    IDs.push_back(10037);
    IDs.push_back(10039);
    IDs.push_back(10046);   // 8

    IDs.push_back(10058);
    IDs.push_back(10080);
    IDs.push_back(10109);
    IDs.push_back(10193);
    IDs.push_back(10224);
    IDs.push_back(10227);
    IDs.push_back(10251);
    IDs.push_back(10268);    // 8

    IDs.push_back(10294);
    IDs.push_back(10306);
    IDs.push_back(10313);
    IDs.push_back(10315);
    IDs.push_back(10332);
    IDs.push_back(10344);
    IDs.push_back(10367);
    IDs.push_back(10380);    // 8

    IDs.push_back(10433);
    IDs.push_back(10443);
    IDs.push_back(10446);
    IDs.push_back(10447);
    IDs.push_back(10499);
    IDs.push_back(10524);
    IDs.push_back(10679);
    IDs.push_back(10695);    // 8

    IDs.push_back(10697);
    IDs.push_back(10763);
    IDs.push_back(11221);
    IDs.push_back(11387);
    IDs.push_back(11388);
    IDs.push_back(11943);
    IDs.push_back(12101);
    IDs.push_back(14386);    // 8

    IDs.push_back(18990);
    IDs.push_back(21727);    // 2

    return IDs;
}

void AstrologyTool::printCurrentAspects() {
    // Calculate Current Aspects
    Calculate::mapAspectsByBody     aspects;
    Calculate::AspectByBodyInserter aspectInserter(aspects);

    Calculate::calculateAspects(aspectTypes, MyDate::getCurrentLocalJulian(), bodyIDs, aspectInserter);

    // Print them
    LogAspects<Calculate::mapAspectsByBody> aspectLogger;
    aspectAction(aspects, aspectLogger);

    StreamAspects<Calculate::mapAspectsByBody> aspectStreamer(cout);
    aspectAction(aspects, aspectStreamer);
}

}   // namespace Matinnia