#include "vecteurs.h"
#include <stdlib.h>

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

// fonction initialisation de la trajectoire
void init_trajectory(trajectory *t, int initial_capacity) {
  t->p = malloc(initial_capacity * sizeof(point));
  if (t->p == NULL) {
    // erreur d'allocation memoire
    exit(EXIT_FAILURE);
  }
  t->size = 0;
  t->capacity = initial_capacity;
}

// fonctiona ajout de points
void add_point(trajectory *t, point new_point) {
  // Si le tableau est plein alors on l'agrendi.
  if (t->size >= t->capacity) {
    t->capacity *= 2; // On double la capacité
    t->p = realloc(t->p, t->capacity * sizeof(point));

    if (t->p == NULL) {
      // erreur de reallocation memoire
      exit(EXIT_FAILURE);
    }
  }

  // On ajoute le point 
  t->p[t->size] = new_point;
  // on incrémente la taille
  t->size++;
}

// fonction liberation de la memoire
void free_trajectory(trajectory* t) {
    free(t->p);
    t->p = NULL;
    t->size = 0;
    t->capacity = 0;
}
