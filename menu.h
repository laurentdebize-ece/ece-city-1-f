#ifndef ECE_CITY_1_F_MENU_H
#define ECE_CITY_1_F_MENU_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

enum Menu {MENU, REGLES, EQUIPE, JOUER, FIN};


typedef struct {
    int mode_de_jeu ;
    ALLEGRO_BITMAP* batimentDeco[] ;
}Menu;

void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) ;
void dessinerEquipe(Menu* menu, ALLEGRO_FONT* font, float width, float height, float mouse_x, float mouse_y) ;
void ntmsalefidpute(ALLEGRO_BITMAP* taMereLaPutamadre) ;

#endif //ECE_CITY_1_F_MENU_H
