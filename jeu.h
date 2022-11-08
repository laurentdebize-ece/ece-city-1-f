#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"
#define NBICONE 10
#define COLONNE 45
#define LIGNE 35

enum BATIMENTS{RIEN, ROUTE, CENTRALE, CHATEAU, TERRAIN, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL};
enum Niveau{ROUTIER, EAU, ELECTRICITE};



typedef struct{
    int secondes, minutes ;
} Temps ;

typedef struct{
    int x, y, type ;
}Case;

typedef struct {
    int nbHabitants, width, height, mouse_x, mouse_y ;
    bool mouseIsPressed;
    int niveauAfficher, objetSelectionne ;
    Case map[COLONNE][LIGNE] ;
    Temps time ;
    Bitmap icone[NBICONE] ;
} Jeu ;

void initJeu(Jeu* jeu) ;
void temps(Temps* time, int compteur) ;

void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) ;

int determinerCaseX(int mouse_x) ;
int determinerCaseY(int mouse_y) ;

void dessinerTerrain() ;

#endif //ECE_CITY_1_F_JEU_H
