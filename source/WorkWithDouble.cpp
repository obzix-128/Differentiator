#include "WorkWithDouble.h"

bool isItAboutSame(double first_numeral, double second_numeral)
{
    const double ALMOST_ZERO = 1e-6;
    if(fabs(first_numeral - second_numeral) < ALMOST_ZERO)
    {
        return true;
    }

    return false;
}
