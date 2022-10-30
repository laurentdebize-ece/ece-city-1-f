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
}Menu;

void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) ;

#endif //ECE_CITY_1_F_MENU_H
