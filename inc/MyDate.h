#ifndef MATINNIA_MYDATE_H
#define MATINNIA_MYDATE_H

// C++ Libraries
#include <ctime>

#include <ostream>
using std::ostream;

#include <string>
using std::string;

// Project Headers
#include "MiscDefinitions.h"

namespace Matinnia {

class MyDate {
private:

    double julianDate;

	// Constants
    static const double MAX_JULIAN;
    static const double MIN_JULIAN;
    static const int    MAX_YEAR = 99999;
    static const int    MIN_YEAR = -99999;


public:

    enum MONTH {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    MyDate();
    MyDate(const MyDate& date);
    explicit MyDate(const time_t time);
    explicit MyDate(const double julianDate);
    MyDate(const int year, const MONTH month = JANUARY, const size_t day = 1,
           const size_t hour = 0, const size_t minute = 0, const size_t second = 0);
    ~MyDate();

    inline double       getJulianDate() const    { return julianDate; }
    inline long         getYear() const          { long result = 0; julian2Gregorian(julianDate, &result); return result; }

    tm                  getTM_Struct() const;
    void                updateTime();

    static size_t       dayOfWeek(const long year, const MONTH month, const size_t day);

    static double       getCurrentLocalJulian();
    static double       getCurrentUTJulian();

    static double       gregorian2Julian(const long year, const MONTH month = JANUARY, const size_t day = 1,
                                         const size_t hour = 0, const size_t minute = 0, const size_t second = 0);

    inline static double    time_t2Julian(const time_t time)    { return MyDate(time).getJulianDate(); }

    static IS_VALID     julian2Gregorian(const double julianDate, long* const year, MONTH* const month = NULL, size_t* const day = NULL,
                                         size_t* const hour = NULL, size_t* const minute = NULL, size_t* const second = NULL);

    static IS_VALID     validateFebruary(const size_t day, const int year);
    static IS_VALID     validateGregorian(const int year, const MONTH month = JANUARY, const size_t day = 1,
                                          const size_t hour = 0, const size_t minute = 0, const size_t second = 0);
    static IS_VALID     validateJulian(const double julianDate);
    static IS_VALID     validateMonthDay(const MONTH month, const size_t day, const int year);
    static IS_VALID     validateTime(const size_t hour, const size_t minute, const size_t second);

    static bool         isLeapYear(const int year);
    static MONTH        int2MONTH(const int month);
    static void         MONTH2String(const MONTH month, string& output);
    static size_t       MONTH2int(const MONTH month);
};  // class MyDate

ostream&     operator<< (ostream& out, const MyDate& RHS);
string&      operator<< (string& out, const MyDate& RHS);

}   // namespace Matinnia

#endif  // MATINNIA_MYDATE_H