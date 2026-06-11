#ifndef VECTEURS_H
#define VECTEURS_H

// Vector structure
typedef struct {
  double x, y, z;
} vector;

// Point structure
typedef struct {
  vector r; // position
  vector v; // vitesse
  double t; // temps
} point;

// Trajectory
typedef struct {
  point* p;
  int size;   
  int capacity; // nombre de points max avant de devoir re-allouer de la memoire
} trajectory;

// Planet structure
typedef struct {
  vector pos; // position
  vector spe;  // vitesse (speed)
  vector acc; // acceleration
  char *name; // nom
  double mass; // masse
  trajectory traj; // trajectoire
  double perih; // perihelie
  double dga; // demi-grand axe
  double e;  // excentricite
} planet;

// Vectors functions
vector vec_add(vector a, vector b);
vector vec_sub(vector a, vector b);
vector vec_scale(vector v, double s);
double vec_norm(vector v);

void init_trajectory(trajectory* t, int initial_capacity);
void add_point(trajectory *t, point new_point);
void free_trajectory(trajectory* t);

vector accel(vector position);


#endif
