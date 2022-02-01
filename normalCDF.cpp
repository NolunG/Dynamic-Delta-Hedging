#include "normalCDF.h"
#include <stdio.h>
#include "math.h"

normalCDF::normalCDF()
{
}

normalCDF::~normalCDF()
{
}

double normalCDF::cdfFromZ(double x)
{   double z = 0, Rz = 0, N = 0;
     if (x < 0) {
        x = -x;
        z = 1.0 / (1.0 + B * x);
        Rz = A1 * z + A2 * pow(z, 2) + A3 * pow(z, 3) + A4 * pow(z, 4) + A5 * pow(z, 5);
        N =  NORMALIZER * exp(-0.5 * pow(x, 2)) * Rz;
        //N = 1 - N;
    } else {
        z = 1.0 / (1.0 + B * x);
        Rz = A1 * z + A2 * pow(z, 2) + A3 * pow(z, 3) + A4 * pow(z, 4) + A5 * pow(z, 5);
        N = 1 - NORMALIZER * exp(-0.5 * pow(x, 2)) * Rz;
    }
    return N;
}
