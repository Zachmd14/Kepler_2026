#include "constants.h"
#include "functions.h"
#include "vecteurs.h"
#include <stdio.h>

int main() {

  printf(";============================================================\n");
  printf("TEST 1: Vector Scaling (vec_scale)\n");
  printf(";============================================================\n");

  vector vecteur;
  vecteur.x = 2;
  vecteur.y = 4;
  vecteur.z = 6;
  vecteur = vec_scale(vecteur, 2);
  printf("Should be 4\n");
  printf("value of x : %f\n", vecteur.x);

  printf(";============================================================\n");
  printf("TEST 2: Planet Perihelion Calculation (calculDistancePerihelie)\n");
  printf(";============================================================\n");

  planet terre;
  terre.name = "Terre";
  terre.mass = masseTerre;
  terre.dga = dgaTerre;
  terre.e = exTerre;
  terre.perih = calculDistancePerihelie(terre);
  printf("Should be 147 098 291...\n");
  printf("perihelie terre : %f\n", terre.perih);

  printf(";============================================================\n");
  printf("TEST 3: Trajectory Initialization and Point Addition\n");
  printf(";============================================================\n");

  planet planeteTest;
  planeteTest.name = "test planet";
  planeteTest.mass = masseTerre;
  planeteTest.dga = dgaTerre;
  planeteTest.e = exTerre;
  planeteTest.perih = calculDistancePerihelie(planeteTest);

  init_trajectory(&planeteTest.traj, 10);
  for (int i = 0; i < 10; ++i) {
    point pt;
    pt.t = i;
    pt.r.x = i * 1.5;
    pt.r.y = 0.0;
    pt.r.z = 0.0;
    pt.v.x = 0.0;
    pt.v.y = 2.5;
    pt.v.z = 0.0;
    add_point(&planeteTest.traj, pt);
  }

  printf("Nombre de points enregistres : %d\n", planeteTest.traj.size);
  for (int i = 0; i < planeteTest.traj.size; i++) {
    printf("Temps : %f -> Position X : %f\n", planeteTest.traj.p[i].t,
           planeteTest.traj.p[i].r.x);
  }

  int coef = 0;
  printf("Nombre d'annees a simuler : ");
  scanf("%d", &coef);
  int nbPas = 365 * coef;

  printf(";============================================================\n");
  printf("TEST 4: Test trajectoire\n");
  printf(";============================================================\n");

  // --- Terre ---

  planet terreEulerSimple;
  terreEulerSimple.name = "Terre Euler Simple";
  terreEulerSimple.mass = masseTerre;
  terreEulerSimple.dga = dgaTerre;
  terreEulerSimple.e = exTerre;
  terreEulerSimple.perih = calculDistancePerihelie(terreEulerSimple);
  init_trajectory(&terreEulerSimple.traj, nbPas);
  point departTerre;
  departTerre.r.x = terreEulerSimple.perih;
  departTerre.r.y = 0.0;
  departTerre.r.z = 0.0;
  departTerre.v.x = 0.0;
  departTerre.v.y = calculVitessePerihelie(terreEulerSimple);
  departTerre.v.z = 0.0;
  departTerre.t = 0.0;
  add_point(&terreEulerSimple.traj, departTerre);
  eulerSimple(&terreEulerSimple, nbPas);

  planet terreEulerAsym;
  terreEulerAsym.name = "Terre Euler Asymetrique";
  terreEulerAsym.mass = masseTerre;
  terreEulerAsym.dga = dgaTerre;
  terreEulerAsym.e = exTerre;
  terreEulerAsym.perih = calculDistancePerihelie(terreEulerAsym);
  init_trajectory(&terreEulerAsym.traj, nbPas);
  add_point(&terreEulerAsym.traj, departTerre);
  eulerAsym(&terreEulerAsym, nbPas);

  planet terreRungeKutta;
  terreRungeKutta.name = "Terre Runge-Kutta 2";
  terreRungeKutta.mass = masseTerre;
  terreRungeKutta.dga = dgaTerre;
  terreRungeKutta.e = exTerre;
  terreRungeKutta.perih = calculDistancePerihelie(terreRungeKutta);
  init_trajectory(&terreRungeKutta.traj, nbPas);
  add_point(&terreRungeKutta.traj, departTerre);
  rungeKutta2(&terreRungeKutta, nbPas);

  // --- Mercure ---

  planet mercureEulerSimple;
  mercureEulerSimple.name = "Mercure Euler Simple";
  mercureEulerSimple.mass = masseMercure;
  mercureEulerSimple.dga = dgaMercure;
  mercureEulerSimple.e = exMercure;
  mercureEulerSimple.perih = calculDistancePerihelie(mercureEulerSimple);
  init_trajectory(&mercureEulerSimple.traj, nbPas);
  point departMercure;
  departMercure.r.x = mercureEulerSimple.perih;
  departMercure.r.y = 0.0;
  departMercure.r.z = 0.0;
  departMercure.v.x = 0.0;
  departMercure.v.y = calculVitessePerihelie(mercureEulerSimple);
  departMercure.v.z = 0.0;
  departMercure.t = 0.0;
  add_point(&mercureEulerSimple.traj, departMercure);
  eulerSimple(&mercureEulerSimple, nbPas);
  /* printf("Mercure - Marge de difference Em (Euler Simple) : %e\n",
   * energieMecanique(&mercureEulerSimple, energieCSV)); */

  planet mercureEulerAsym;
  mercureEulerAsym.name = "Mercure Euler Asymetrique";
  mercureEulerAsym.mass = masseMercure;
  mercureEulerAsym.dga = dgaMercure;
  mercureEulerAsym.e = exMercure;
  mercureEulerAsym.perih = calculDistancePerihelie(mercureEulerAsym);
  init_trajectory(&mercureEulerAsym.traj, nbPas);
  add_point(&mercureEulerAsym.traj, departMercure);
  eulerAsym(&mercureEulerAsym, nbPas);

  planet mercureRungeKutta;
  mercureRungeKutta.name = "Mercure Runge-Kutta 2";
  mercureRungeKutta.mass = masseMercure;
  mercureRungeKutta.dga = dgaMercure;
  mercureRungeKutta.e = exMercure;
  mercureRungeKutta.perih = calculDistancePerihelie(mercureRungeKutta);
  init_trajectory(&mercureRungeKutta.traj, nbPas);
  add_point(&mercureRungeKutta.traj, departMercure);
  rungeKutta2(&mercureRungeKutta, nbPas);

  // --- Venus ---

  planet venusEulerSimple;
  venusEulerSimple.name = "Venus Euler Simple";
  venusEulerSimple.mass = masseVenus;
  venusEulerSimple.dga = dgaVenus;
  venusEulerSimple.e = exVenus;
  venusEulerSimple.perih = calculDistancePerihelie(venusEulerSimple);
  init_trajectory(&venusEulerSimple.traj, nbPas);
  point departVenus;
  departVenus.r.x = venusEulerSimple.perih;
  departVenus.r.y = 0.0;
  departVenus.r.z = 0.0;
  departVenus.v.x = 0.0;
  departVenus.v.y = calculVitessePerihelie(venusEulerSimple);
  departVenus.v.z = 0.0;
  departVenus.t = 0.0;
  add_point(&venusEulerSimple.traj, departVenus);
  eulerSimple(&venusEulerSimple, nbPas);
  /* printf("Venus  - Marge de difference Em (Euler Simple)  : %e\n",
   * energieMecanique(&venusEulerSimple, energieCSV)); */

  planet venusEulerAsym;
  venusEulerAsym.name = "Venus Euler Asymetrique";
  venusEulerAsym.mass = masseVenus;
  venusEulerAsym.dga = dgaVenus;
  venusEulerAsym.e = exVenus;
  venusEulerAsym.perih = calculDistancePerihelie(venusEulerAsym);
  init_trajectory(&venusEulerAsym.traj, nbPas);
  add_point(&venusEulerAsym.traj, departVenus);
  eulerAsym(&venusEulerAsym, nbPas);

  planet venusRungeKutta;
  venusRungeKutta.name = "Venus Runge-Kutta 2";
  venusRungeKutta.mass = masseVenus;
  venusRungeKutta.dga = dgaVenus;
  venusRungeKutta.e = exVenus;
  venusRungeKutta.perih = calculDistancePerihelie(venusRungeKutta);
  init_trajectory(&venusRungeKutta.traj, nbPas);
  add_point(&venusRungeKutta.traj, departVenus);
  rungeKutta2(&venusRungeKutta, nbPas);

  // --- Mars ---

  planet marsEulerSimple;
  marsEulerSimple.name = "Mars Euler Simple";
  marsEulerSimple.mass = masseMars;
  marsEulerSimple.dga = dgaMars;
  marsEulerSimple.e = exMars;
  marsEulerSimple.perih = calculDistancePerihelie(marsEulerSimple);
  init_trajectory(&marsEulerSimple.traj, nbPas);
  point departMars;
  departMars.r.x = marsEulerSimple.perih;
  departMars.r.y = 0.0;
  departMars.r.z = 0.0;
  departMars.v.x = 0.0;
  departMars.v.y = calculVitessePerihelie(marsEulerSimple);
  departMars.v.z = 0.0;
  departMars.t = 0.0;
  add_point(&marsEulerSimple.traj, departMars);
  eulerSimple(&marsEulerSimple, nbPas);
  /* printf("Mars   - Marge de difference Em (Euler Simple)  : %e\n",
   * energieMecanique(&marsEulerSimple, energieCSV)); */

  planet marsEulerAsym;
  marsEulerAsym.name = "Mars Euler Asymetrique";
  marsEulerAsym.mass = masseMars;
  marsEulerAsym.dga = dgaMars;
  marsEulerAsym.e = exMars;
  marsEulerAsym.perih = calculDistancePerihelie(marsEulerAsym);
  init_trajectory(&marsEulerAsym.traj, nbPas);
  add_point(&marsEulerAsym.traj, departMars);
  eulerAsym(&marsEulerAsym, nbPas);

  planet marsRungeKutta;
  marsRungeKutta.name = "Mars Runge-Kutta 2";
  marsRungeKutta.mass = masseMars;
  marsRungeKutta.dga = dgaMars;
  marsRungeKutta.e = exMars;
  marsRungeKutta.perih = calculDistancePerihelie(marsRungeKutta);
  init_trajectory(&marsRungeKutta.traj, nbPas);
  add_point(&marsRungeKutta.traj, departMars);
  rungeKutta2(&marsRungeKutta, nbPas);

  // --- Export JSON ---

  FILE *fichier = fopen("trajectoire.json", "w");
  if (fichier == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }

  // fichier trajectoires.json avec toutes les planetes
  fprintf(fichier, "{\n");
  exportJson(&terreEulerSimple, fichier);
  fprintf(fichier, ",\n");
  exportJson(&terreEulerAsym, fichier);
  fprintf(fichier, ",\n");
  exportJson(&terreRungeKutta, fichier);
  fprintf(fichier, ",\n");
  exportJson(&mercureEulerSimple, fichier);
  fprintf(fichier, ",\n");
  exportJson(&mercureEulerAsym, fichier);
  fprintf(fichier, ",\n");
  exportJson(&mercureRungeKutta, fichier);
  fprintf(fichier, ",\n");
  exportJson(&venusEulerSimple, fichier);
  fprintf(fichier, ",\n");
  exportJson(&venusEulerAsym, fichier);
  fprintf(fichier, ",\n");
  exportJson(&venusRungeKutta, fichier);
  fprintf(fichier, ",\n");
  exportJson(&marsEulerSimple, fichier);
  fprintf(fichier, ",\n");
  exportJson(&marsEulerAsym, fichier);
  fprintf(fichier, ",\n");
  exportJson(&marsRungeKutta, fichier);
  fprintf(fichier, "\n}\n");
  fclose(fichier);

  // fichiers individuels

  // --- Terre ---
  FILE *fTerreEulerSimple = fopen("trajectoireTerreEulerSimple.json", "w");
  if (fTerreEulerSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&terreEulerSimple, fTerreEulerSimple);

  FILE *fTerreEulerAsym = fopen("trajectoireTerreEulerAsym.json", "w");
  if (fTerreEulerAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&terreEulerAsym, fTerreEulerAsym);
  FILE *fTerreRungeKutta = fopen("trajectoireTerreRungeKutta.json", "w");
  if (fTerreRungeKutta == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&terreRungeKutta, fTerreRungeKutta);
  fclose(fTerreRungeKutta);

  // --- MERCURE ---
  FILE *fMercureEulerSimple = fopen("trajectoireMercureEulerSimple.json", "w");
  if (fMercureEulerSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&mercureEulerSimple, fMercureEulerSimple);
  fclose(fMercureEulerSimple);

  FILE *fMercureEulerAsym = fopen("trajectoireMercureEulerAsym.json", "w");
  if (fMercureEulerAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&mercureEulerAsym, fMercureEulerAsym);
  fclose(fMercureEulerAsym);

  FILE *fMercureRungeKutta = fopen("trajectoireMercureRungeKutta.json", "w");
  if (fMercureRungeKutta == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&mercureRungeKutta, fMercureRungeKutta);
  fclose(fMercureRungeKutta);

  // --- VENUS ---
  FILE *fVenusEulerSimple = fopen("trajectoireVenusEulerSimple.json", "w");
  if (fVenusEulerSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&venusEulerSimple, fVenusEulerSimple);
  fclose(fVenusEulerSimple);

  FILE *fVenusEulerAsym = fopen("trajectoireVenusEulerAsym.json", "w");
  if (fVenusEulerAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&venusEulerAsym, fVenusEulerAsym);
  fclose(fVenusEulerAsym);

  FILE *fVenusRungeKutta = fopen("trajectoireVenusRungeKutta.json", "w");
  if (fVenusRungeKutta == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&venusRungeKutta, fVenusRungeKutta);
  fclose(fVenusRungeKutta);

  // --- MARS ---
  FILE *fMarsEulerSimple = fopen("trajectoireMarsEulerSimple.json", "w");
  if (fMarsEulerSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&marsEulerSimple, fMarsEulerSimple);
  fclose(fMarsEulerSimple);

  FILE *fMarsEulerAsym = fopen("trajectoireMarsEulerAsym.json", "w");
  if (fMarsEulerAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&marsEulerAsym, fMarsEulerAsym);
  fclose(fMarsEulerAsym);

  FILE *fMarsRungeKutta = fopen("trajectoireMarsRungeKutta.json", "w");
  if (fMarsRungeKutta == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  exportJson(&marsRungeKutta, fMarsRungeKutta);
  fclose(fMarsRungeKutta);

  // Energies mecaniques

  // --- TERRE ---

  FILE *fEnergieTerreSimple = fopen("energiesTerreEulerSimple.csv", "w");
  if (fEnergieTerreSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Terre - Marge de difference Em (Euler Simple)    : %e\n",
         energieMecanique(&terreEulerSimple, fEnergieTerreSimple));
  fclose(fEnergieTerreSimple);

  FILE *fEnergieTerreAsym = fopen("energiesTerreEulerAsym.csv", "w");
  if (fEnergieTerreAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Terre - Marge de difference Em (Euler Asym)      : %e\n",
         energieMecanique(&terreEulerAsym, fEnergieTerreAsym));
  fclose(fEnergieTerreAsym);

  FILE *fEnergieTerreRK = fopen("energiesTerreRungeKutta.csv", "w");
  if (fEnergieTerreRK == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Terre - Marge de difference Em (Runge-Kutta)    : %e\n",
         energieMecanique(&terreRungeKutta, fEnergieTerreRK));
  fclose(fEnergieTerreRK);

  // --- MERCURE ---

  FILE *fEnergieMercureSimple = fopen("energiesMercureEulerSimple.csv", "w");
  if (fEnergieMercureSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mercure - Marge de difference Em (Euler Simple)  : %e\n",
         energieMecanique(&mercureEulerSimple, fEnergieMercureSimple));
  fclose(fEnergieMercureSimple);

  FILE *fEnergieMercureAsym = fopen("energiesMercureEulerAsym.csv", "w");
  if (fEnergieMercureAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mercure - Marge de difference Em (Euler Asym)    : %e\n",
         energieMecanique(&mercureEulerAsym, fEnergieMercureAsym));
  fclose(fEnergieMercureAsym);

  FILE *fEnergieMercureRK = fopen("energiesMercureRungeKutta.csv", "w");
  if (fEnergieMercureRK == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mercure - Marge de difference Em (Runge-Kutta)  : %e\n",
         energieMecanique(&mercureRungeKutta, fEnergieMercureRK));
  fclose(fEnergieMercureRK);

  // --- VENUS ---

  FILE *fEnergieVenusSimple = fopen("energiesVenusEulerSimple.csv", "w");
  if (fEnergieVenusSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Venus - Marge de difference Em (Euler Simple)    : %e\n",
         energieMecanique(&venusEulerSimple, fEnergieVenusSimple));
  fclose(fEnergieVenusSimple);

  FILE *fEnergieVenusAsym = fopen("energiesVenusEulerAsym.csv", "w");
  if (fEnergieVenusAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Venus - Marge de difference Em (Euler Asym)      : %e\n",
         energieMecanique(&venusEulerAsym, fEnergieVenusAsym));
  fclose(fEnergieVenusAsym);

  FILE *fEnergieVenusRK = fopen("energiesVenusRungeKutta.csv", "w");
  if (fEnergieVenusRK == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Venus - Marge de difference Em (Runge-Kutta)    : %e\n",
         energieMecanique(&venusRungeKutta, fEnergieVenusRK));
  fclose(fEnergieVenusRK);

  // --- MARS ---

  FILE *fEnergieMarsSimple = fopen("energiesMarsEulerSimple.csv", "w");
  if (fEnergieMarsSimple == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mars - Marge de difference Em (Euler Simple)     : %e\n",
         energieMecanique(&marsEulerSimple, fEnergieMarsSimple));
  fclose(fEnergieMarsSimple);

  FILE *fEnergieMarsAsym = fopen("energiesMarsEulerAsym.csv", "w");
  if (fEnergieMarsAsym == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mars - Marge de difference Em (Euler Asym)       : %e\n",
         energieMecanique(&marsEulerAsym, fEnergieMarsAsym));
  fclose(fEnergieMarsAsym);

  FILE *fEnergieMarsRK = fopen("energiesMarsRungeKutta.csv", "w");
  if (fEnergieMarsRK == NULL) {
    printf("Erreur ouverture fichier\n");
    return 1;
  }
  printf("Mars - Marge de difference Em (Runge-Kutta)     : %e\n",
         energieMecanique(&marsRungeKutta, fEnergieMarsRK));
  fclose(fEnergieMarsRK);

  free_trajectory(&terreEulerSimple.traj);
  free_trajectory(&terreEulerAsym.traj);
  free_trajectory(&terreRungeKutta.traj);
  free_trajectory(&mercureEulerSimple.traj);
  free_trajectory(&mercureEulerAsym.traj);
  free_trajectory(&mercureRungeKutta.traj);
  free_trajectory(&venusEulerSimple.traj);
  free_trajectory(&venusEulerAsym.traj);
  free_trajectory(&venusRungeKutta.traj);
  free_trajectory(&marsEulerSimple.traj);
  free_trajectory(&marsEulerAsym.traj);
  free_trajectory(&marsRungeKutta.traj);

  return 0;
}
