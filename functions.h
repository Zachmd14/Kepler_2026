#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vecteurs.h"
#include "constants.h"
#include <stdio.h>

double calculDistancePerihelie(planet p);
double calculVitessePerihelie(planet p);

void eulerSimple(planet *p, int step, double t);
void exportJson(planet *p, FILE *fichier);

#endif
