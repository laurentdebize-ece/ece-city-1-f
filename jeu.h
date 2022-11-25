#ifndef ECE_CITY_1_F_JEU_H
#define ECE_CITY_1_F_JEU_H
#include "menu.h"
#include <stdio.h>
#define NBICONE 15
#define NBHABITATIONS 6
#define NBROUTE 5
#define COLONNE 45
#define LIGNE 35
#define MAX 20
#define PI 3.14159265358979323846
#define MAPX 290
#define MAPY 60
#define CASEX_X (float)26
#define ARGENTDEP 500000000
#define CAPACITE 5000
#include "eva.h"
#include "stdlib.h"


enum Batiments{NUL, NUL1, NUL2, NUL3, NUL4, RIEN, ROUTE, CENTRALE, CHATEAU};
enum Habitations {TERRAIN, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, CONSTRUCTION};
enum Niveau{ROUTIER, EAU, ELECTRICITE};
enum DirectionRoute{HAUT, BAS, DROITE, GAUCHE};


typedef struct{
    float dixieme ;
    int secondes, minutes ;
} Temps ;

typedef struct{
    float x, y ;
    int type, route[4], rotation, distanceX, distanceY, numConstruction ;
    int electricite, eau ;
}Case;

typedef struct {
    int quantitedistri,type, tempsChateau;
    int caseX, caseY;
}Chateau;

typedef struct {
    int quantitedistri,type, tempsCentrale, electricite, capaciteElec;
    int caseX, caseY;
}Centralelectrique;

typedef struct{
    int caseX, caseY, type, tempsEvolution, evolution, provenanceElec, distance, nbHabitant;
    int filePrioriteDistance[10] ;
}Habitation;

typedef struct{
    int z, direction[4] ;
    float mapX, oldMapX, mapY, oldMapY ;
    float CaseX_X, oldCaseX_X ;
}Zoom;

typedef struct{
    int distance;
    int quatntitedistribue;
    int capacite;
}Matricechat;

typedef struct {
    float width, height,toolboxX ;       // Info écran
    int mouse_x, mouse_y ;
    int niveauAfficher, objetSelectionne ;   //Selection
    int nbCentrale, nbMaisons, nbChateau, nbHabitants, argent ; //Info du jeu
    int capaciteEau, capacitElec;
    bool mouseIsPressed;

    //STRUCTURE
    Centralelectrique tabCentrale[MAX];  //Différentes structures du jeu
    Chateau tabChateau[MAX];
    Habitation tabHabitations[MAX];

    //GRILLE
    Case map[COLONNE+1][LIGNE+1] ;

    int matriceChateau_Maison[COLONNE][LIGNE] ;

    //TEMPS
    Temps time[2];

    //ZOOM
    Zoom zoom ;

    //Matrice chateau d'eau
    Matricechat** matrice;

    //BITMAP
    Bitmap icone[NBICONE]  ;
    Bitmap habitations[NBHABITATIONS] ;
    Bitmap route[NBROUTE] ;
    Bitmap centrale[3] ;
} Jeu ;

void initJeu(Jeu* jeu) ;
void initImage(Jeu** jeu) ;
void temps(Temps* time, int compteur, int numTimer) ;
void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) ;
void dessinerNiveau(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu** jeu) ;
void dessinerToolbox(Jeu* jeu) ;
int prioDistance (Jeu *jeu, int quelleMaison);
void barreicone(ALLEGRO_FONT*smallFont ,Jeu*jeu) ;

void determinerDistanceCentrale(Jeu** jeu, int quelChateau) ;

int determinerCaseX(int mouse_x, int mapX, int caseX_X) ;
int determinerCaseY(int mouse_y, int mapY, int caseX_X) ;

bool verifierTerrain3_3v2(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool verifierTerrain4_6(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool routeProximiteMaison(Jeu **jeu, int caseSourisX, int caseSourisY);
bool routeProximiteCentrale(Jeu** jeu, int caseSourisX, int caseSourisY) ;
bool verifierPlacementTerrain(Jeu* jeu, int caseX, int caseY) ;
bool verifierPlacementCentrale(Jeu* jeu, int caseX, int caseY, int type) ;
int determinerDistanceMaison(Jeu** jeu,int quelleMaison) ;


//Affichage de la route
void verifierAffichageRoute(Jeu** jeu, int caseSourisX, int caseSourisY) ;
int combinaison(Jeu jeu, int caseSourisX, int caseSourisY, int* rotation) ;


//Affichage du terrain (la grille)
void dessinerTerrain(Jeu* jeu) ;
void zoom(Jeu* jeu, int caseX, int caseY) ;
void deplacerMap(Jeu* jeu) ;
int verifCentrale(Jeu* jeu, Habitation tabHabitations[jeu->nbHabitants],int i);


#endif //ECE_CITY_1_F_JEU_H
