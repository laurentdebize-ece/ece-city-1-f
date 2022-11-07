#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"


typedef struct{
    int secondes, minutes ;
} Temps ;

typedef struct {
    int nbHabitants, width, height ;
    Temps time ;
    ALLEGRO_BITMAP* bitmap[] ;
} Jeu ;

void initJeu(Jeu* jeu) ;
void temps(Temps* time, int compteur) ;

void dessinerJeu(ALLEGRO_FONT* font, Jeu* jeu) ;
void dessinerTerrain() ;

#endif //ECE_CITY_1_F_JEU_H
