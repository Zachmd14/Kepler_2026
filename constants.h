#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

static const double dgaTerre = 149597887500.0; // Demi-grand axe de la Terre
static const double masseTerre = 5.9722*pow(10, 24); // Masse de la Terre
static const double exTerre = 0.0167; // Excentricite de l'orbite terrestre

static const double dgaMercure = 579090500000.0; //Demi-grand axe de Mercure
static const double masseMercure = 3.285*pow(10 , 23); // Masse de Mercure
static const double exMercure = 0.21; // Excentricite de l'orbite de Mercure


static const double dgaVenus = 108 209 500000.0; //Demi-grand axe de Venus
static const double masseVenus = 4.867*pow(10 , 24); // Masse de Venus
static const double exVenus = 0.0068; // Excentricite de l'orbite de Venus


static const double dgaMars = 227939200000.0; // Demi-grand axe de Mars
static const double masseMars = 6.4171*pow(10 , 23); // Masse de Mars
static const double exMars = 0.0167; // Excentricite de l'orbite de Mars

static const double masseSoleil = 1.9884*pow(10, 30); // Masse du soleil

static const double constanteGravitation = 6.67259*pow(10,-11); // Constante Gravitationnelle

static const double DT = 86400.0; // Pas en une journee
#endif    
