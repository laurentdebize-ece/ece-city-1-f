#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"


typedef struct{
    int secondes, minutes ;
} Temps ;

typedef struct {
    Temps time ;
    int nbHabitants ;
} Jeu ;

void initJeu(Jeu* jeu) ;
void temps(Temps* time, int compteur) ;

void dessinerJeu(ALLEGRO_FONT* font, Jeu jeu, float width, float height) ;


#endif //ECE_CITY_1_F_JEU_H
