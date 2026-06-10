#ifndef VECTEURS_H
#define VECTEURS_H

/*
 * Planet code struct, with position, speed and trajectory
 */
struct vector
{
  double pos_x;
  double spe_x;

  double pos_y;
  double spe_y;

  double pos_z;
  double spe_z;
};

struct trajectory
{
  char name[50];
  double points[];
  
};


#endif
