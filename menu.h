#ifndef ECE_CITY_1_F_MENU_H
#define ECE_CITY_1_F_MENU_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#define NBDECO 10


enum Menu {MENU, REGLES, EQUIPE, JOUER, FIN};


typedef struct{
    ALLEGRO_BITMAP* image ;
    int width, height ;
}Bitmap;

typedef struct {
    int mode_de_jeu ;
    Bitmap deco[NBDECO] ;
}Menu;

void initBitmapDeco(Menu* menu) ;
void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) ;
void dessinerEquipe(Menu* menu, ALLEGRO_FONT* font, float width, float height, float mouse_x, float mouse_y) ;

#endif //ECE_CITY_1_F_MENU_H
