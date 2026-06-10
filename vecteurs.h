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

// Planet structure
typedef struct {
  char name[50];
  double mass;
  // trajectory;
  double periph;
} planet;

// Functions definitions
vector vec_add(vector a, vector b);
vector vec_sub(vector a, vector b);
vector vec_scale(vector v, double s);
double vec_norm(vector v);

#endif
