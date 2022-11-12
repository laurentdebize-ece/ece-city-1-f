#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"
#include <stdio.h>
#define NBICONE 10
#define NBHABITATIONS 6
#define NBROUTE 5
#define COLONNE 45
#define LIGNE 35
#define MAX 150
#define PI 3.14159265358979323846
#define CAPACITE 5000


enum Batiments{NUL, NUL1, NUL2, NUL3, NUL4, RIEN, ROUTE, CENTRALE, CHATEAU};
enum Habitations {TERRAIN, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, CONSTRUCTION};
enum Niveau{ROUTIER, EAU, ELECTRICITE};
enum DirectionRoute{HAUT, BAS, DROITE, GAUCHE};


typedef struct{
    int secondes, minutes ;
} Temps ;

typedef struct{
    float x, y ;
    int type, route[4], rotation ;
}Case;

typedef struct {
    int quantitedistri,type, tempsChateau;
    float x, y;
    Bitmap bitmapeau;
}Chateau;

typedef struct {
    int quantitedistri,type, tempsCentrale;
    float x, y;
    Bitmap bitmapcen;
}Centralelectrique;

typedef struct{
    int caseX, caseY, type, tempsEvolution, evolution ;
    Bitmap habitation;
}Habitation;


typedef struct {
    //ENTIER
    float width, height ;       // Info écran
    int mouse_x, mouse_y ;
    int capaciteElec, capaciteEau;
    int niveauAfficher, objetSelectionne ;   //Selection
    int nbCentrale, nbMaisons, nbChateau, nbHabitants, argent ; //Info du jeu
    bool mouseIsPressed;

    //STRUCTURE
    Centralelectrique tabCentrale[MAX];  //Différentes structures du jeu
    Chateau tabChateau[MAX];
    Habitation tabHabitations[MAX];

    //GRILLE
    Case map[MAX][MAX] ;

    //TEMPS
    Temps time[2];

    //BITMAP
    Bitmap icone[NBICONE]  ;
    Bitmap habitations[NBHABITATIONS] ;
    Bitmap route[NBROUTE] ;
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
bool verifierPlacementTerrain(Jeu* jeu, int caseX, int caseY) ;


//Affichage de la route
void verifierAffichageRoute(Jeu** jeu, int caseSourisX, int caseSourisY) ;
int combinaison(Jeu jeu, int caseSourisX, int caseSourisY, int* rotation) ;

void dessinerTerrain() ;

#endif //ECE_CITY_1_F_JEU_H
