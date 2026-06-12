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

  planet test2;
  test2.name = "Planete test 2";
  test2.mass = masseTerre;
  test2.dga = dgaTerre;
  test2.e = exTerre;
  test2.perih = calculDistancePerihelie(test2);

  int step = 365 * 10;
  init_trajectory(&test2.traj, step);

  // Points de departs
  point depart;
  depart.r.x = test2.perih; // placée sur l'axe X à la périhélie
  depart.r.y = 0.0;
  depart.r.z = 0.0;
  depart.v.x = 0.0;
  depart.v.y = calculVitessePerihelie(test2); // vitesse perpendiculaire, sur Y
  depart.v.z = 0.0;
  depart.t = 0.0;
  add_point(&test2.traj, depart);

  eulerSimple(&test2, step);

  // Export en JSON
  FILE *fichier = fopen("trajectoire.json", "w");
  if (fichier == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Fichier trajectoire.json genere avec %d points\n",
         test2.traj.size);

  printf(";============================================================\n");
  printf("TEST 4: Test Ep\n");
  printf(";============================================================\n");

  printf("Marge de difference Em : %e\n", energieMecanique(&test2));

  planet test3;
  test3.name = "Planete test 3";
  test3.mass = masseTerre;
  test3.dga = dgaTerre;
  test3.e = exTerre;
  test3.perih = calculDistancePerihelie(test3);

  init_trajectory(&test3.traj, step);

  // Points de departs
  depart.r.x = test3.perih;
  depart.r.y = 0.0;
  depart.r.z = 0.0;
  depart.v.x = 0.0;
  depart.v.y = calculVitessePerihelie(test3);
  depart.v.z = 0.0;
  depart.t = 0.0;
  add_point(&test3.traj, depart);

  eulerAsym(&test3, step);

  // Export en JSON
  fprintf(fichier, "{\n");
  exportJson(&test2, fichier);
  fprintf(fichier, ",\n");
  exportJson(&test3, fichier);
  fprintf(fichier, "\n}\n");

  fclose(fichier);
  printf("Fichier trajectoire.json genere avec %d points\n",
         test3.traj.size);

  free_trajectory(&test2.traj);
  free_trajectory(&test3.traj);
  return 0;

  /****************************************************************************/
  /* void exportJson(planet * p, FILE * fichier) {			      */
  /*   // Ajoute le nom de la planete					      */
  /*   fprintf(fichier, "\n");						      */
  /*   fprintf(fichier, "{\"%s-euler\": [\n", p->name);			      */
  /* 									      */
  /*   // Ajoute chaque coordonnees					      */
  /*   for (int i = 0; i < p->traj.size; i++) {				      */
  /*     point pt = p->traj.p[i];					      */
  /* 									      */
  /*     fprintf(fichier, "[[%e, %e, %e], [%e, %e, %e], %d]", pt.r.x, pt.r.y, */
  /*             pt.r.z, pt.v.x, pt.v.y, pt.v.z, (int)pt.t);		      */
  /* 									      */
  /*     // Si dernier element -> virgule, sinon non			      */
  /*     if (i < p->traj.size - 1)					      */
  /*       fprintf(fichier, ",\n");					      */
  /*     else								      */
  /*       fprintf(fichier, "\n");					      */
  /*   }								      */
  /* 									      */
  /*   // On fini le fichier						      */
  /*   fprintf(fichier, "]}\n");					      */
  /* }									      */
  /****************************************************************************/
}
