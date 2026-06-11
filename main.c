#include "constants.h"
#include "functions.h"
#include "vecteurs.h"
#include <stdio.h>

int main() {

  vector test;
  test.x = 2;
  test.y = 4;
  test.z = 6;

  test = vec_scale(test, 2);
  printf("value of x : %f\n", test.x);

  planet t;
  t.name = "Terre";
  t.mass = masseTerre;
  t.dga = dgaTerre;
  t.e = exTerre;  
  t.perih = calculDistancePerihelie(t);
  
  printf("perihelie terre : %f\n", t.perih);

  return 0;
}
