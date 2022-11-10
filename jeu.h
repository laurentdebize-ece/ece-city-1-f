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
    float x, y ;
    int type ;
}Case;

typedef struct {
    int quantitedistri,type;
    float x, y;
    Bitmap bitmapeau;
}Chateau;

typedef struct {
    int quantitedistri,type;
    float x, y;
    Bitmap bitmapcen;
}Centralelectrique;

typedef struct{
    int caseX,caseY,type;
    Bitmap habitation;
    int tempsEvolution, evolution ;
}Habitation;


typedef struct {
    float width, height ;       // Info écran
    int mouse_x, mouse_y ;
    int niveauAfficher, objetSelectionne ;   //Selection
    int nbCentrale, nbMaisons, nbChateau, nbHabitants, argent ; //Info du jeu
    bool mouseIsPressed;
    Centralelectrique tabCentrale;  //Différentes structures du jeu
    Chateau tabChateau;
    Habitation tabHabitations[MAX];
    Case map[COLONNE][LIGNE] ;
    Temps time[2];
    Bitmap icone[NBICONE]  ;
} Jeu ;

void initJeu(Jeu* jeu) ;
void temps(Temps* time, int compteur, int numTimer) ;
void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) ;

int determinerCaseX(int mouse_x) ;
int determinerCaseY(int mouse_y) ;

bool verifierTerrain3_3v2(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool verifierTerrain4_6(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool routeProximiteMaison(Jeu **jeu, int caseSourisX, int caseSourisY);
bool routeProximiteCentrale(Jeu** jeu, int caseSourisX, int caseSourisY) ;

void dessinerTerrain() ;
void mettreCentrale();

#endif //ECE_CITY_1_F_JEU_H
