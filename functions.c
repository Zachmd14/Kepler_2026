#include "functions.h"
#include "constants.h"
#include "vecteurs.h"
#include <math.h>

double calculDistancePerihelie(planet p) {
  double result;
  result = p.dga * (1 - p.e);
  return result;
}

double calculVitessePerihelie(planet p) {
  double result = sqrt(
      (constanteGravitation * masseSoleil * (1 + p.e) / p.dga * (1 - p.e)));
  return result;
}
