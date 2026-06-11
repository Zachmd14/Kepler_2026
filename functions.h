#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vecteurs.h"
#include "constants.h"

double calculDistancePerihelie(planet p);
double calculVitessePerihelie(planet p);

void eulerSimple(planet p, vector pos, int step, double t);

#endif
