#ifndef MATINNIA_LOGGER_H
#define MATINNIA_LOGGER_H

// PREPROCESSING
#ifdef _DEBUG
#define LOGGER
#endif

// C++ Libraries
#include <ctime>
#include <cstdio>

// Project Headers
#include "MiscDefinitions.h"
#include "MyDate.h"
using namespace Matinnia;


namespace Matinnia {

// Singleton class
class Logger {
public:
    inline static Logger&       getInstance()   { static Logger instance; return instance; }
    static const unsigned int   LOG_MAX = 256;
    static char                 logMessage[LOG_MAX];
    
    bool            openLog(const char* const fileName);
    inline void     closeLog()  { if (NULL != logFile) { fclose(logFile); logFile = NULL; } }
    bool            writeStatus() const;
    bool            writeStatus(const char* const status) const;


private:
    // Unusable Constructors/Destructors
    Logger();
    Logger(const Logger& RHS);
    Logger& operator= (const Logger& RHS);
    ~Logger();

    // Data
    static char         messageTime[LOG_MAX];
    FILE*               logFile;
    static unsigned int count;
    time_t              creationTime;
    clock_t             creationClock;

    // Methods
    inline static double    getCPUClockTime(const clock_t startCPUTime, const clock_t endCPUTime) {     return (static_cast<double>(endCPUTime) - static_cast<double>(startCPUTime)) / CLOCKS_PER_SEC; }
    inline static double    getWallClockTime(const time_t startTime, const time_t endTime)   { return difftime(endTime, startTime); }
    static void             formattedDateTime(const time_t time);
};

}   // end namespace Matinnia
#endif //   end MATINNIA_LOGGER_H
