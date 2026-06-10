#include "vecteurs.h"

// Add two vectors coordinates
vector vec_add(vector a, vector b) {
  vector result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

// Substract two vectors coordinates
vector vec_sub(vector a, vector b) {
  vector result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

// Scale a vector with a double
vector vec_scale(vector v, double s) {
  vector result;
  result.x = v.x * s;
  result.y = v.y * s;
  result.z = v.z * s;
  return result;
}
