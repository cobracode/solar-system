// C++ Libraries
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif

//#include <thread>
//using std::thread;
#include <vector>
using std::vector;

// Project Headers
#include "AspectType.h"
#include "AstrologyTool.h"
#include "Calculate.h"
#include "Logger.h"
#include "SwissEphemerisInterface.h"

void playGround() {
    Logger& log(Logger::getInstance());
    log.openLog("MyLog.txt");

    Calculate::mapAspectsByOrb aspectsByOrb;
    Calculate::AspectByOrbInserter insertByOrb(aspectsByOrb);

    Calculate::mapAspectsByBody aspectsByBody;
    Calculate::AspectByBodyInserter insertByBody(aspectsByBody);

    Calculate::logAspectMap(aspectsByOrb);
    Calculate::logAspectMap(aspectsByBody);
}


int main(int, char** const) {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_crtBreakAlloc = 343;
#endif

    AstrologyTool tool;

    tool.printCurrentAspects();    

    //logCurrentAspects();
    //logAspectsBetween(me, lorianne);

    //int* nums = new int[3];

    //nums[0] = 0;
    //nums[1] = 1;
    //nums[2] = 2;

    //thread a(test::func, nums);
    //a.join();

    //delete[] nums;

    //playGround();
    //SwissEphemerisInterface::close();
    printf("%ld\n\n", clock());
    return 0;
}