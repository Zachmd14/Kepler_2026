#include "functions.h"
#include "constants.h"
#include "vecteurs.h"
#include <math.h>
#include <stdatomic.h>
#include <stddef.h>
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
void eulerSimple(planet *p, int step) {
  /*
   * accell = dv_x / dt
   * position a t_n+1 : r = r + v * dt
   * vitesse a t_n+1 : v = v + a * dt
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

// Euler asym
void eulerAsym(planet *p, int step) {
  /*
   * accell = dv_x / dt
   * vitesse a t_n+1 : v = v + a * dt
   * position a t_n+1 : r = r + v_tn+1 * dt
   */

  // Initial values
  vector pos = p->traj.p[0].r;
  vector v = p->traj.p[0].v;
  double t = p->traj.p[0].t;

  // Euler calcul loop
  for (int i = 0; i < step; ++i) {
    vector acc = accel(pos);

    // Calculating new possitions
    vector newVit = vec_add(v, vec_scale(acc, DT));
    vector newPos = vec_add(pos, vec_scale(newVit, DT));
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

double energieMecanique(planet *p) {
  double eP = 0;
  double eC = 0;
  double eM = 0;
  double numEp = constanteGravitation * p->mass * masseSoleil; // numerateur Ep
  double denEp = 0;                                            // numerateur Ec
  double max_eM = 0;
  double min_eM = 0;

  for (int i = 0; i < p->traj.size; ++i) {

    // Energie potentielle
    denEp = vec_norm(p->traj.p[i].r);
    if (denEp < 0) {
      denEp = denEp * (-1);
    }
    eP = -(numEp / denEp);

    // Energie cinetique
    eC = (1.0 / 2.0) * p->mass *
         (vec_norm(p->traj.p[i].v) * vec_norm(p->traj.p[i].v));

    // Energie mecanique
    eM = eP + eC;
    /* printf("valeur de eM au pas %d : %e\n", i, eM); */

    // Calcul ecart

    if (eM > max_eM) {
      max_eM = eM;
    }

    if (eM < min_eM) {
      min_eM = eM;
    }
  };
  double ecartEm = max_eM - min_eM;
  return ecartEm;
}

// Runge-Kutta ordre 2 (methode du point milieu)
void rungeKutta2(planet *p, int step) {
  /*
   * k1 = f(t, y)
   * k2 = f(t + dt/2, y + dt/2 * k1)
   * y_n+1 = y_n + dt * k2
   */

  // Initial values
  vector pos = p->traj.p[0].r;
  vector v = p->traj.p[0].v;
  double t = p->traj.p[0].t;

  for (int i = 0; i < step; ++i) {
    // k1
    vector k1_pos = v;
    vector k1_vit = accel(pos);

    // Point milieu
    vector pos_mid = vec_add(pos, vec_scale(k1_pos, DT / 2.0));
    vector vit_mid = vec_add(v, vec_scale(k1_vit, DT / 2.0));

    // k2 (evalue au point milieu)
    vector k2_pos = vit_mid;
    vector k2_vit = accel(pos_mid);

    // Mise a jour finale
    vector newPos = vec_add(pos, vec_scale(k2_pos, DT));
    vector newVit = vec_add(v, vec_scale(k2_vit, DT));
    t += DT;

    // Ajout du nouveau point
    point newPoint;
    newPoint.r = newPos;
    newPoint.v = newVit;
    newPoint.t = t;
    add_point(&p->traj, newPoint);

    // Mise a jour pour la prochaine iteration
    pos = newPos;
    v = newVit;
  }
}
