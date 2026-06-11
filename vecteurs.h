#ifndef VECTEURS_H
#define VECTEURS_H

// Vector structure
typedef struct {
  double x, y, z;
} vector;

// Point structure
typedef struct {
  vector r;
  vector v;
  double t;
} point;

// Trajectory
typedef struct {
  point* p;
  int size;   
  int capacity;
} trajectory;

// Planet structure
typedef struct {
  char *name;
  double mass; // masse
  trajectory traj; // trajectoire
  double perih; // perihelie
  double dga; // demi-grand axe
  double e;  // excentricite
} planet;

// Functions definitions
vector vec_add(vector a, vector b);
vector vec_sub(vector a, vector b);
vector vec_scale(vector v, double s);
double vec_norm(vector v);

#endif
