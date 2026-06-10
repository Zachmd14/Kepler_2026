#ifndef VECTEURS_H
#define VECTEURS_H

typedef struct {
    double x, y, z;
} vector;

vector vec_add(vector a, vector b);
vector vec_sub(vector a, vector b);
vector vec_scale(vector v, double s);
double vec_norm(vector v);


#endif
