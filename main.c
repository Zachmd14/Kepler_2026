#include <stdio.h>
#include "vecteurs.h"
#include "constants.h"

int main(){

  vector test;  
  test.x=2;
  test.y=4;
  test.z=6;

  test = vec_scale(test, 2);
  printf("value of x : %f\n", test.x);
  return 0;
}
