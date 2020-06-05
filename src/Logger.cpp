// Own header
#include "Logger.h"
using namespace Matinnia;

// C/C++ Libraries
#include <cstring>

char Logger::logMessage[Logger::LOG_MAX] = {'\0'};
char Logger::messageTime[Logger::LOG_MAX] = {'\0'};
unsigned int Logger::count = 0;

Logger::Logger() :
    logFile(NULL)
{
    // Log creation time
    creationTime = time(NULL);
    creationClock = clock();
}

Logger::~Logger() {
    if (NULL != logFile) {
        time_t destructTime = time(NULL);

        // Write destruction time
        sprintf(logMessage, "**********        LOG DESTRUCTION  [%.20f]: clock = %10ld        **********\n\n"
                            " CPU Time: %f seconds.\n"
                            " Wall Time: %f seconds.\n\n",
                MyDate::time_t2Julian(destructTime), clock(), getCPUClockTime(creationClock, clock()), getWallClockTime(creationTime, destructTime));

        writeStatus();

        // Close log file
        closeLog();
    }
}


void Logger::formattedDateTime(const time_t time) {
    const tm* const structTime = localtime(&time);

    sprintf(messageTime, "%10ld--%4d.%02d%02d.%02d%02d.%02d",
            ++count,
            structTime->tm_year + 1900,
            structTime->tm_mon + 1,
            structTime->tm_mday,
            structTime->tm_hour,
            structTime->tm_min,
            structTime->tm_sec);
}


bool Logger::openLog(const char* const fileName) {
    bool returnVal = false;

    logFile = fopen(fileName, "w");

    if (NULL != logFile) {
        sprintf(logMessage, "**********        LOG CREATION     [%.20f]: clock = %10ld        **********",
                MyDate::time_t2Julian(creationTime), creationClock);

        writeStatus();
        returnVal = true;
    }
    else {
        printf("\n\nERROR: Failed to open log file [%s].\n\n", fileName);
    }

    return returnVal;
}


bool Logger::writeStatus() const {
    bool returnVal = false;

    if (NULL != logFile) {
        formattedDateTime(time(NULL));

        fprintf(logFile, "%s%10ld    ---    %s\n", messageTime, clock(), logMessage);

        returnVal = true;
    }

    return returnVal;
}


bool Logger::writeStatus(const char* const status) const {
    bool returnVal = false;

    if (NULL != logFile) {
        formattedDateTime(time(NULL));

        fprintf(logFile, "%s%10ld    ---    %s\n", messageTime, clock(), status);

        returnVal = true;
    }

    return returnVal;
}
