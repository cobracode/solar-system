// Project Headers
#include "Logger.h"
#include "SwissEphemerisInterface.h"
#include "ZodiacPosition.h"
using namespace Matinnia;
using namespace SwissEphemerisInterface;

// Non-const Static data
bool    isInitialized       = false;


int SwissEphemerisInterface::body2Int(const COSMIC_BODY body) {
    int returnVal = -999;

    switch (body) {
        case SUN:               returnVal = 0;  break;
        case MOON:              returnVal = 1;  break;
        case MERCURY:           returnVal = 2;  break;
        case VENUS:             returnVal = 3;  break;
        case MARS:              returnVal = 4;  break;
        case JUPITER:           returnVal = 5;  break;
        case SATURN:            returnVal = 6;  break;
        case URANUS:            returnVal = 7;  break;
        case NEPTUNE:           returnVal = 8;  break;
        case PLUTO:             returnVal = 9;  break;
        case NODE_MEAN:         returnVal = 10; break;
        case NODE_TRUE:         returnVal = 11; break;
        case APOGEE_MEAN:       returnVal = 12; break;
        case APOGEE_OSCULATING: returnVal = 13; break;
        case EARTH:             returnVal = 14; break;
        case CHIRON:            returnVal = 15; break;
        case PHOLUS:            returnVal = 16; break;
        case CERES:             returnVal = 17; break;
        case PALLAS:            returnVal = 18; break;
        case JUNO:              returnVal = 19; break;
        case VESTA:             returnVal = 20; break;
        default:                returnVal = 99; break;
    }

    return returnVal;
}


void SwissEphemerisInterface::body2String(const COSMIC_BODY body, char* const output) {
    switch (body) {
        case SUN:               strcpy(output, "Sun");                      break;
        case MOON:              strcpy(output, "Moon");                     break;
        case MERCURY:           strcpy(output, "Mercury");                  break;
        case VENUS:             strcpy(output, "Venus");                    break;
        case MARS:              strcpy(output, "Mars");                     break;
        case JUPITER:           strcpy(output, "Jupiter");                  break;
        case SATURN:            strcpy(output, "Saturn");                   break;
        case URANUS:            strcpy(output, "Uranus");                   break;
        case NEPTUNE:           strcpy(output, "Neptune");                  break;
        case PLUTO:             strcpy(output, "Pluto");                    break;
        case NODE_MEAN:         strcpy(output, "North Node (mean)");        break;
        case NODE_TRUE:         strcpy(output, "North Node (true)");        break;
        case APOGEE_MEAN:       strcpy(output, "Apogee (mean)");            break;
        case APOGEE_OSCULATING: strcpy(output, "Apogee (osculating)");      break;
        case EARTH:             strcpy(output, "Earth");                    break;
        case CHIRON:            strcpy(output, "Chiron");                   break;
        case PHOLUS:            strcpy(output, "Pholus");                   break;
        case CERES:             strcpy(output, "Ceres");                    break;
        case PALLAS:            strcpy(output, "Pallas Athene");            break;
        case JUNO:              strcpy(output, "Juno");                     break;
        case VESTA:             strcpy(output, "Vesta");                    break;
        case PSYCHE:            strcpy(output, "Psyche");                   break;
        case SAPPHO:            strcpy(output, "Sappho");                   break;
        case AMBROSIA:          strcpy(output, "Ambrosia");                 break;
        case EROS:              strcpy(output, "Eros");                     break;
        case VALENTINE:         strcpy(output, "Valentine");                break;
        case CUPIDO:            strcpy(output, "Cupido");                   break;
        case AMOR:              strcpy(output, "Amor");                     break;
        case APHRODITE:         strcpy(output, "Aphrodite");                break;
        case ANTEROS:           strcpy(output, "Anteros");                  break;
        case ADONIS:            strcpy(output, "Adonis");                   break;
        case LUST:              strcpy(output, "Lust");                     break;
        case COMPASSION:        strcpy(output, "Compassion");               break;
        case SWEET:             strcpy(output, "Sweet");                    break;
        default:                strcpy(output, "UNKNOWN BODY");             break;
    }
}


double SwissEphemerisInterface::getPlanetLongitude(const COSMIC_BODY body, const double julianDayUT) {
    double          result                  = 0.0;

    if (true == SwissEphemerisInterface::isInitialized) {
        double  callResult[6];
        char    serr[256];

        if (0 > swe_calc_ut(julianDayUT, body2Int(body), 0, callResult, serr)) {
            char    bodyName[21];
            body2String(body, bodyName);
            sprintf(Logger::logMessage, "An error occurred while computing the longitude for cosmic body %s: %s.",
                    bodyName, serr);

            Logger::getInstance().writeStatus();
        }
        else {
            result = callResult[0];
        }
    }
    else {
        char    bodyName[21];
        body2String(body, bodyName);
        sprintf(Logger::logMessage, "Unable to compute longitude for cosmic body %s at UT Julian %f; Swiss Ephemeris not initialized.",
                bodyName, julianDayUT);

        Logger::getInstance().writeStatus();
    }

    return result;
}


double SwissEphemerisInterface::getPlanetLongitude(const int body, const double julianDayUT) {
    double          result                  = 0.0;

    if (true == SwissEphemerisInterface::isInitialized) {
        double  callResult[6];
        char    serr[256];

        if (0 > swe_calc_ut(julianDayUT, body, 0, callResult, serr)) {
            char    bodyName[21];
            int2BodyString(body, bodyName);
            sprintf(Logger::logMessage, "An error occurred while computing the longitude for cosmic body %s: %s.",
                    bodyName, serr);

            Logger::getInstance().writeStatus();
        }
        else {
            result = callResult[0];
        }
    }
    else {
        char    bodyName[21];
        int2BodyString(body, bodyName);
        sprintf(Logger::logMessage, "Unable to compute longitude for cosmic body %s at UT Julian %f; Swiss Ephemeris not initialized.",
                bodyName, julianDayUT);

        Logger::getInstance().writeStatus();
    }

    return result;
}


bool SwissEphemerisInterface::initializeSwiss(const char* const swissDir) {
    if (false == isInitialized && NULL != swissDir) {
        swe_set_ephe_path(const_cast<char*>(swissDir));

        SwissEphemerisInterface::isInitialized = true;
#ifdef LOGGER 
        sprintf(Logger::logMessage, "Swiss Ephemeris path initialized to %s.", swissDir);
#endif
    }
    else {
#ifdef LOGGER
        sprintf(Logger::logMessage, "Swiss Ephemeris already initialized; not initializing.");
#endif
    }
#ifdef LOGGER
    Logger::getInstance().writeStatus();
#endif
    return isInitialized;
}


void SwissEphemerisInterface::close() {
    if (true == isInitialized) {
        swe_close();
        isInitialized = false;
    }
}


COSMIC_BODY SwissEphemerisInterface::int2Body(const unsigned int bodyInt) {
    COSMIC_BODY returnVal;

    switch (bodyInt) {
        case 0:         returnVal = SUN;                break;
        case 1:         returnVal = MOON;               break;
        case 2:         returnVal = MERCURY;            break;
        case 3:         returnVal = VENUS;              break;
        case 4:         returnVal = MARS;               break;
        case 5:         returnVal = JUPITER;            break;
        case 6:         returnVal = SATURN;             break;
        case 7:         returnVal = URANUS;             break;
        case 8:         returnVal = NEPTUNE;            break;
        case 9:         returnVal = PLUTO;              break;
        case 10:        returnVal = NODE_MEAN;          break;
        case 11:        returnVal = NODE_TRUE;          break;
        case 12:        returnVal = APOGEE_MEAN;        break;
        case 13:        returnVal = APOGEE_OSCULATING;  break;
        case 14:        returnVal = EARTH;              break;
        case 15:        returnVal = CHIRON;             break;
        case 16:        returnVal = PHOLUS;             break;
        case 17:        returnVal = CERES;              break;
        case 18:        returnVal = PALLAS;             break;
        case 19:        returnVal = JUNO;               break;
        case 20:        returnVal = VESTA;              break;
        case 10016:     returnVal = PSYCHE;             break;
        case 10080:     returnVal = SAPPHO;             break;
        case 10193:     returnVal = AMBROSIA;           break;
        case 10433:     returnVal = EROS;               break;
        case 10447:     returnVal = VALENTINE;          break;
        case 10763:     returnVal = CUPIDO;             break;
        case 11221:     returnVal = AMOR;               break;
        case 11388:     returnVal = APHRODITE;          break;
        case 11943:     returnVal = ANTEROS;            break;
        case 12101:     returnVal = ADONIS;             break;
        case 14386:     returnVal = LUST;               break;
        case 18990:     returnVal = COMPASSION;         break;
        case 21727:     returnVal = SWEET;              break;
        default:        returnVal = EARTH;              break;
    }

    return returnVal;
}


void SwissEphemerisInterface::int2BodyString(const int bodyInt, char* const output) {
    switch (bodyInt) {
        case 0:     strcpy(output, "Sun");                      break;
        case 1:     strcpy(output, "Moon");                     break;
        case 2:     strcpy(output, "Mercury");                  break;
        case 3:     strcpy(output, "Venus");                    break;
        case 4:     strcpy(output, "Mars");                     break;
        case 5:     strcpy(output, "Jupiter");                  break;
        case 6:     strcpy(output, "Saturn");                   break;
        case 7:     strcpy(output, "Uranus");                   break;
        case 8:     strcpy(output, "Neptune");                  break;
        case 9:     strcpy(output, "Pluto");                    break;
        case 10:    strcpy(output, "North Node (mean)");        break;
        case 11:    strcpy(output, "North Node (true)");        break;
        case 12:    strcpy(output, "Apogee (mean)");            break;
        case 13:    strcpy(output, "Apogee (osculating)");      break;
        case 14:    strcpy(output, "Earth");                    break;
        case 15:    strcpy(output, "Chiron");                   break;
        case 16:    strcpy(output, "Pholus");                   break;
        case 17:    strcpy(output, "Ceres");                    break;
        case 18:    strcpy(output, "Pallas Athene");            break;
        case 19:    strcpy(output, "Juno");                     break;
        case 20:    strcpy(output, "Vesta");                    break;
        case 10015:     strcpy(output, "Eunomia");              break;
        case 10016:     strcpy(output, "Psyche");               break;
        case 10019:     strcpy(output, "Fortuna");              break;
        case 10023:     strcpy(output, "Thalia");               break;
        case 10030:     strcpy(output, "Urania");               break;
        case 10037:     strcpy(output, "Fides");                break;
        case 10039:     strcpy(output, "Laetitia");             break;
        case 10046:     strcpy(output, "Hestia");               break;
        case 10058:     strcpy(output, "Concordia");            break;
        case 10080:     strcpy(output, "Sappho");               break;
        case 10109:     strcpy(output, "Felicitas");            break;
        case 10193:     strcpy(output, "Ambrosia");             break;
        case 10224:     strcpy(output, "Oceana");               break;
        case 10227:     strcpy(output, "Philosophia");          break;
        case 10251:     strcpy(output, "Sophia");               break;
        case 10268:     strcpy(output, "Adorea");               break;
        case 10294:     strcpy(output, "Felicia");              break;
        case 10306:     strcpy(output, "Unitas");               break;
        case 10313:     strcpy(output, "Chaldea");              break;
        case 10315:     strcpy(output, "Constantia");           break;
        case 10332:     strcpy(output, "Siri");                 break;
        case 10344:     strcpy(output, "Desiderata");           break;
        case 10367:     strcpy(output, "Amicitia");             break;
        case 10380:     strcpy(output, "Fiducia");              break;
        case 10433:     strcpy(output, "Eros");                 break;
        case 10443:     strcpy(output, "Photographia");         break;
        case 10446:     strcpy(output, "Aeternitas");           break;
        case 10447:     strcpy(output, "Valentine");            break;
        case 10499:     strcpy(output, "Venusia");              break;
        case 10524:     strcpy(output, "Fidelio");              break;
        case 10679:     strcpy(output, "Pax");                  break;
        case 10695:     strcpy(output, "Bella");                break;
        case 10697:     strcpy(output, "Galilea");              break;
        case 10763:     strcpy(output, "Cupido");               break;
        case 11221:     strcpy(output, "Amor");                 break;
        case 11387:     strcpy(output, "Kama");                 break;
        case 11388:     strcpy(output, "Aphrodite");            break;
        case 11943:     strcpy(output, "Anteros");              break;
        case 12101:     strcpy(output, "Adonis");               break;
        case 14386:     strcpy(output, "Lust");                 break;
        case 18990:     strcpy(output, "Compassion");           break;
        case 21727:     strcpy(output, "Sweet");                break;



        default:        strcpy(output, "UNKNOWN BODY");         break;
    }
}


bool SwissEphemerisInterface::string2Body(const string& bodyString, COSMIC_BODY& output) {
    bool success = false;

    if (false == bodyString.empty()) {
        if ("Sun" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Moon" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Mercury" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Venus" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Mars" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Jupiter" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Saturn" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Uranus" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Neptune" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Pluto" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("North Node (mean)" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("North Node (true)" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Apogee (mean)" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Apogee (osculating)" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Earth" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Chiron" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Pholus" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Ceres" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Pallas Athene" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Juno" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("Vesta" == bodyString) {
            output = SUN;
            success = true;
        }
        else if ("UNKNOWN BODY" == bodyString) {
            output = SUN;
            success = true;
        }
    }

    return success;
}