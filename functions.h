#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vecteurs.h"
#include "constants.h"
#include <stdio.h>

double calculDistancePerihelie(planet p);
double calculVitessePerihelie(planet p);

void eulerSimple(planet *p, int step);
void eulerAsym(planet *p, int step);

void rungeKutta2(planet *p, int step);

void exportJson(planet *p, FILE *fichier);

double energieMecanique(planet *p);

void diagnostique(planet *p, FILE *fichier); // Fais un diagnostique complet de la planete et le met dans un fichier

#endif
