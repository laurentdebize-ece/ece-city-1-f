#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"
#define NBICONE 10
#define COLONNE 45
#define LIGNE 35
#define MAX 150
#define CAPACITE 5000

enum BATIMENTS{RIEN, ROUTE, CENTRALE, CHATEAU, TERRAIN, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL};
enum Niveau{ROUTIER, EAU, ELECTRICITE};


typedef struct{
    int secondes, minutes ;
} Temps ;

typedef struct{
    int x, y, type ;
}Case;

typedef struct {
    int quantitedistri;
    int x, y,type;
    Bitmap bitmapeau;
}Chateau;

typedef struct {
    int quantitedistri;
    int x, y,type;
    Bitmap bitmapcen;
}Centralelectrique;

typedef struct{
    int x,y,type;
    Bitmap habitation;
}Habitation;


typedef struct {
    int nbHabitants, width, height, mouse_x, mouse_y ;
    int argent;
    int nbcentrale, nbMaisons ;
    Centralelectrique tabcentrale;
    int nbchateau;
    Chateau tabchat;
    Habitation tabhabitation[MAX];
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
bool verifierTerrain3_3(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool verifierTerrain3_3v2(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool routeProximite(Jeu **jeu, int caseSourisx, int caseSourisy);

void dessinerTerrain() ;
void mettreCentrale();

#endif //ECE_CITY_1_F_JEU_H
