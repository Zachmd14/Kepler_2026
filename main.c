#include "constants.h"
#include "functions.h"
#include "vecteurs.h"
#include <stdio.h>

int main() {

  printf(";============================================================\n");
  printf("TEST 1: Vector Scaling (vec_scale)\n");
  printf(";============================================================\n");
  vector test;
  test.x = 2;
  test.y = 4;
  test.z = 6;

  test = vec_scale(test, 2);
  printf("Should be 4\n");
  printf("value of x : %f\n", test.x);

  printf(";============================================================\n");
  printf("TEST 2: Planet Perihelion Calculation (calculDistancePerihelie)\n");
  printf(";============================================================\n");
  planet t;
  t.name = "Terre";
  t.mass = masseTerre;
  t.dga = dgaTerre;
  t.e = exTerre;
  t.perih = calculDistancePerihelie(t);

  printf("Should be 147 098 291...\n");
  printf("perihelie terre : %f\n", t.perih);

  printf(";============================================================\n");
  printf("TEST 3: Trajectory Initialization and Point Addition\n");
  printf(";============================================================\n");
  planet tp;
  tp.name = "test planet";
  tp.mass = masseTerre;
  tp.dga = dgaTerre;
  tp.e = exTerre;
  tp.perih = calculDistancePerihelie(t);

  init_trajectory(&tp.traj, 10);
  for (int i = 0; i < 10; ++i) {
    point act;
    act.t = i;

    act.r.x = i * 1.5;
    act.r.y = 0.0;
    act.r.z = 0.0;
    act.v.x = 0.0;
    act.v.y = 2.5;
    act.v.z = 0.0;

    add_point(&tp.traj, act);
  }

  printf("Nombre de points enregistres : %d\n", tp.traj.size);
  for (int i = 0; i < tp.traj.size; i++) {
    printf("Temps : %f -> Position X : %f\n", tp.traj.p[i].t, tp.traj.p[i].r.x);
  }

  return 0;
}
