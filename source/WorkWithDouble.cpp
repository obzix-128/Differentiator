#include "WorkWithDouble.h"

#define ALMOST_ZERO 1e-6

bool isItAboutSame(double first_numeral, double second_numeral)
{
    if(fabs(first_numeral - second_numeral) < ALMOST_ZERO)
    {
        return true;
    }

    return false;
}
