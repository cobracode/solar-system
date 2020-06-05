// Own header
#include "MyDate.h"
using namespace Matinnia;

// C++ Libraries
#include <ctime>

#include <iomanip>
using std::setprecision;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// Static Constants
const double MyDate::MAX_JULIAN = 999999999.99999;
const double MyDate::MIN_JULIAN = -999999999.99999;


MyDate::MyDate() : julianDate(0.0) {
    // Default date is to initialize to current datetime
    time_t  currentTime(time(NULL));
    tm*     localTime(localtime(&currentTime));

    julianDate = gregorian2Julian(localTime->tm_year + 1900, int2MONTH(localTime->tm_mon + 1), C(size_t, localTime->tm_mday),
                                  C(size_t, localTime->tm_hour), C(size_t, localTime->tm_min), C(size_t, localTime->tm_sec));
}


MyDate::MyDate(const MyDate& date) : julianDate(date.julianDate) {}


MyDate::MyDate(const double julianDate) : julianDate(julianDate) {}


MyDate::MyDate(const int year, const MONTH month, const size_t day,
               const size_t hour, const size_t minute, const size_t second) : julianDate(0.0) {
    // If Gregorian date is valid, compute to Julian date
    if (VALID == validateGregorian(year, month, day, hour, minute, second)) {
        julianDate = gregorian2Julian(year, month, day, hour, minute, second);
    }
}


MyDate::MyDate(const time_t time) {
    // Convert time_t to tm
    tm* structTime(localtime(&time));

    // Calculate julianDate from structTime
    julianDate = gregorian2Julian(structTime->tm_year + 1900, int2MONTH(structTime->tm_mon + 1), C(size_t, structTime->tm_mday),
                                  C(size_t, structTime->tm_hour), C(size_t, structTime->tm_min), C(size_t, structTime->tm_sec));
}


MyDate::~MyDate() {}


tm MyDate::getTM_Struct() const {
    tm result;

    long            year;
    MyDate::MONTH   month;
    size_t          day;
    size_t          hour;
    size_t          minute;
    size_t          second;

    // Load local date values
    julian2Gregorian(julianDate, &year, &month, &day, &hour, &minute, &second);

    result.tm_year  = year - 1900;
    result.tm_mon   = C(int, MONTH2int(month) - 1);
    result.tm_mday  = C(int, day);
    result.tm_hour  = C(int, hour);
    result.tm_min   = C(int, minute);
    result.tm_sec   = C(int, second);
    result.tm_wday  = C(int, dayOfWeek(year, month, day));
    

    return result;
}


void MyDate::updateTime() {
    time_t  currentTime = time(NULL);
    tm*     localTime   = localtime(&currentTime);

    julianDate = gregorian2Julian(localTime->tm_year + 1900, int2MONTH(localTime->tm_mon + 1), C(size_t, localTime->tm_mday),
                                  C(size_t, localTime->tm_hour), C(size_t, localTime->tm_min), C(size_t, localTime->tm_sec));
}


ostream& Matinnia::operator<< (ostream& out, const MyDate& RHS) {
    tm outputTime = RHS.getTM_Struct();
    out << asctime(&outputTime) << endl;

    return out;
}


string& Matinnia::operator<< (string& out, const MyDate& RHS) {
    tm outputTime = RHS.getTM_Struct();
    out += asctime(&outputTime);

    return out;
}


size_t MyDate::dayOfWeek(const long year, const MyDate::MONTH month, const size_t day) {
    size_t month2 = MONTH2int(month);

    static int  data[]  = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    long        year2   = year;
    year2               -= month2 < 3;

    return (year2 + year2/4 - year2/100 + year2/400 + data[month2 - 1] + day) % 7;
}


double MyDate::getCurrentLocalJulian() {
    time_t  currentTime = time(NULL);
    tm*     localTime   = localtime(&currentTime);

    return gregorian2Julian(localTime->tm_year + 1900, int2MONTH(localTime->tm_mon + 1), C(size_t, localTime->tm_mday),
                            C(size_t, localTime->tm_hour), C(size_t, localTime->tm_min), C(size_t, localTime->tm_sec));
}


double MyDate::getCurrentUTJulian() {
    time_t  currentTime(time(NULL));
    tm*     timeUT(gmtime(&currentTime));

    return gregorian2Julian(timeUT->tm_year + 1900, int2MONTH(timeUT->tm_mon + 1), C(size_t, timeUT->tm_mday),
                            C(size_t, timeUT->tm_hour), C(size_t, timeUT->tm_min), C(size_t, timeUT->tm_sec));
}


MyDate::MONTH MyDate::int2MONTH(const int intMonth) {
    MyDate::MONTH result;

    switch (intMonth) {
        case 1: result = JANUARY; break;
        case 2: result = FEBRUARY; break;
        case 3: result = MARCH; break;
        case 4: result = APRIL; break;
        case 5: result = MAY; break;
        case 6: result = JUNE; break;
        case 7: result = JULY; break;
        case 8: result = AUGUST; break;
        case 9: result = SEPTEMBER; break;
        case 10: result = OCTOBER; break;
        case 11: result = NOVEMBER; break;
        case 12: result = DECEMBER; break;
        default: result = JANUARY; break;
    }

    return result;
}


void MyDate::MONTH2String(const MONTH month, string& output) {
    switch (month) {
        case JANUARY:   output = "January"; break;
        case FEBRUARY:  output = "February"; break;
        case MARCH:     output = "March"; break;
        case APRIL:     output = "April"; break;
        case MAY:       output = "May"; break;
        case JUNE:      output = "June"; break;
        case JULY:      output = "July"; break;
        case AUGUST:    output = "August"; break;
        case SEPTEMBER: output = "September"; break;
        case OCTOBER:   output = "October"; break;
        case NOVEMBER:  output = "November"; break;
        case DECEMBER:  output = "December"; break;
        default:        output = "INVALID MONTH"; break;
    }
}


size_t MyDate::MONTH2int(const MONTH month) {
    size_t result;

    switch (month) {
        case JANUARY:   result = 1; break;
        case FEBRUARY:  result = 2; break;
        case MARCH:     result = 3; break;
        case APRIL:     result = 4; break;
        case MAY:       result = 5; break;
        case JUNE:      result = 6; break;
        case JULY:      result = 7; break;
        case AUGUST:    result = 8; break;
        case SEPTEMBER: result = 9; break;
        case OCTOBER:   result = 10; break;
        case NOVEMBER:  result = 11; break;
        case DECEMBER:  result = 12; break;
        default:        result = 1; break;
    }

    return result;
}


bool MyDate::isLeapYear(const int year) {
    bool result = false;

    if (0 == year % 400) {
        result = true;
    }
    else if (0 == year % 100) {
        ; // false
    }
    else if (0 == year % 4) {
        result = true;
    }

    return result;
}


double MyDate::gregorian2Julian(const long year, const MyDate::MONTH month, const size_t day,
                                const size_t hour, const size_t minute, const size_t second) {
    double julianDate = 0.0;

	// Only calculate Julian date if Gregorian date is valid
    if (VALID == MyDate::validateGregorian(year, month, day, hour, minute, second)) {
        int A = (14 - month) / 12;
        int Y = year + 4800 - A;
        int M = month + 12*A - 3;
		
        const long julianDayNumber = C(long, day + (153*M + 2)/5 + 365*Y + Y/4 - Y/100 + Y/400 - 32045);
		
        julianDate = julianDayNumber + (hour - 12.0)/24.0 + minute/1440.0 + second/86400.0;
    }

    return julianDate;
}


IS_VALID MyDate::julian2Gregorian(const double julianDate, long* const year, MyDate::MONTH* const month, size_t* const day,
                                  size_t* const hour, size_t* const minute, size_t* const second) {
    IS_VALID returnVal = INVALID;

    // Only calculate Gregorian date if Julian date is valid
    if (VALID == MyDate::validateJulian(julianDate)) {
        // From Wikipedia on June 11, 2011
        // http://en.wikipedia.org/wiki/Julian_day		

        // Calculate day
        double  J   = julianDate + 0.5;
        int     j   = static_cast<int>(J) + 32044;
        int     g   = j / 146097;
        int     dg  = j % 146097;
        int     c   = (dg/36524 + 1) * 3/4;
        int     dc  = dg - c*36524;
        int     b   = dc / 1461;
        int     db  = dc % 1461;
        int     a   = (db/365 + 1) * 3/4;
        int     da  = db - a*365;
        int     y   = g*400 + c*100 + b*4 + a;
        int     m   = (da*5 + 308)/153 - 2;
        int     d   = da - (m + 4)*153/5 + 122;
        
        if (NULL != year) {
            *year = y - 4800 + (m + 2)/12;
        }

        if (NULL != month) {
            *month = int2MONTH((m + 2) % 12 + 1);
        }

        if (NULL != day) {
            *day = C(size_t, d + 1);
        }

        // Calculate time
        long ij  = C(long, ((J - C(long, J)) * 86400.0 + 0.5));

        if (NULL != hour) {
            *hour = C(size_t, ij / 3600);
        }

        if (NULL != minute) {
            *minute = C(size_t, (ij / 60) % 60);
        }

        if (NULL != second) {
            *second = C(size_t, ij % 60);
        }

        returnVal = VALID;
    }
    else {
        if (NULL != year) {
            *year = 0;
        }

        if (NULL != month) {
            *month = JANUARY;
        }

        if (NULL != day) {
            *day = 1;
        }

        if (NULL != hour) {
            *hour = 0;
        }

        if (NULL != minute) {
            *minute = 0;
        }

        if (NULL != second) {
            *second = 0;
        }
    }

    return returnVal;
}


IS_VALID MyDate::validateGregorian(const int year, const MyDate::MONTH month, const size_t day,
                                   const size_t hour, const size_t minute, const size_t second) {
	IS_VALID result = INVALID;
	
	if (MIN_YEAR < year	&&
		MAX_YEAR > year	&&
		VALID == validateMonthDay(month, day, year) &&
		VALID == validateTime(hour, minute, second)) {
		result = VALID;		
	}
	
	return result;
}


IS_VALID MyDate::validateJulian(const double julianDate) {
    IS_VALID result = INVALID;

    if (MIN_JULIAN < julianDate &&
        MAX_JULIAN > julianDate) {
        result = VALID;
    }

    return result;
}


IS_VALID MyDate::validateMonthDay(const MyDate::MONTH month, const size_t day, const int year) {
    IS_VALID result = INVALID;

    switch (month) {
        case JANUARY:
        case MARCH:
        case MAY:
        case JULY:
        case AUGUST:
        case OCTOBER:
        case DECEMBER:
            // 31 days: Jan, Mar, May, July, August, October, December
            if (32 > day) {
                result = VALID;
            }
        	
            break;
        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            // 30 days: April, June, September, November
            if (31 > day) {
                result = VALID;
            }
        	
            break;
        case FEBRUARY:
            // 29 days: Feb leap year
            // 28 days: Feb non-leap year
            if (VALID == MyDate::validateFebruary(day, year)) {
                result = VALID;
            }
        	
            break;
        default: break;
    }

    return result;
}


IS_VALID MyDate::validateTime(const size_t hour, const size_t minute, const size_t second) {
    IS_VALID result = INVALID;

    if (24 > hour   &&
        60 > minute &&
        60 > second) {
        result = VALID;
    }

    return result;
}


IS_VALID MyDate::validateFebruary(const size_t day, const int year) {
    IS_VALID result = INVALID;
	
    if (true == isLeapYear(year)) {
        // February has max 29 days
        if (30 > day) {
            result = VALID;
        }
    }
    else {
        // February has max 28 days
        if (29 > day) {
            result = VALID;
        }
    }
	
    return result;
}