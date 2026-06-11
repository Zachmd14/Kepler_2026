#include "functions.h"
#include "constants.h"
#include "vecteurs.h"
#include <math.h>
#include <stdatomic.h>
#include <stdio.h>

double calculDistancePerihelie(planet p) {
  double result;
  result = p.dga * (1 - p.e);
  return result;
}

double calculVitessePerihelie(planet p) {
  double result = sqrt((constanteGravitation * masseSoleil * (1 + p.e)) /
                       (p.dga * (1 - p.e)));
  return result;
}

// euler simple
void eulerSimple(planet *p, int step, double temps) {
  /*
   * accell = dv_x / dt
   * position a t_n+1 : r = r + v * dt
   * vitesse a t_n+1 : v = v * a * dt
   */

  // Initial values
  vector pos = p->traj.p[0].r;
  vector v = p->traj.p[0].v;
  double t = p->traj.p[0].t;

  // Euler calcul loop
  for (int i = 0; i < step; ++i) {
    vector acc = accel(pos);

    // Calculating new possitions
    vector newPos = vec_add(pos, vec_scale(v, DT));
    vector newVit = vec_add(v, vec_scale(acc, DT));
    t += DT;

    // Adding new points to the trajectory
    point newPoint;
    newPoint.r = newPos;
    newPoint.v = newVit;
    newPoint.t = t;
    add_point(&p->traj, newPoint);

    // Changing values for next step
    pos = newPos;
    v = newVit;
  }
}

void exportJson(planet *p, FILE *fichier) {
  // Ajoute le nom de la planete
  fprintf(fichier, "{\"%s-euler\": [\n", p->name);

  // Ajoute chaque coordonnees
  for (int i = 0; i < p->traj.size; i++) {
    point pt = p->traj.p[i];

    fprintf(fichier, "[[%e, %e, %e], [%e, %e, %e], %d]", pt.r.x, pt.r.y, pt.r.z,
            pt.v.x, pt.v.y, pt.v.z, (int)pt.t);

    // Si dernier element -> virgule, sinon non
    if (i < p->traj.size - 1)
      fprintf(fichier, ",\n");
    else
      fprintf(fichier, "\n");
  }

  // On fini le fichier
  fprintf(fichier, "]}\n");
}
