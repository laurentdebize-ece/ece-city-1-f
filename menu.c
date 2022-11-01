#include "menu.h"


void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) {
    float largeur = 2;
    double color = 2.5;
    ///MENU D'AFFICHAGE
    for (int i = 0; i < 40; i++) {
        al_draw_line(357, 300 + i * largeur, 662, 300 + i * largeur,
                     al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(357, 430 + i * largeur, 662, 430 + i * largeur,
                     al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(357, 560 + i * largeur, 662, 560 + i * largeur,
                     al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
    }
    al_draw_rectangle(357, 300, 662, 380, al_map_rgb(0, 0, 0), 1.5 * largeur);
    al_draw_rectangle(357, 430, 662, 510, al_map_rgb(0, 0, 0), 1.5 * largeur);
    al_draw_rectangle(357, 560, 662, 640, al_map_rgb(0, 0, 0), 1.5 * largeur);

    ///JOUER
    if (mouse_x > 357 && mouse_x < 662 && mouse_y > 300 && mouse_y < 380) {
        al_draw_rectangle(357, 300, 662, 380, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(337, 340, 302, 310, 302, 370, al_map_rgb(232, 30, 23));
        al_draw_triangle(337, 340, 302, 310, 302, 370, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(682, 340, 717, 310, 717, 370, al_map_rgb(232, 30, 23));
        al_draw_triangle(682, 340, 717, 310, 717, 370, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }
    ///REGLES
    if (mouse_x > 357 && mouse_x < 662 && mouse_y > 430 && mouse_y < 510) {
        al_draw_rectangle(357, 430, 662, 510, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(337, 470, 302, 440, 302, 500, al_map_rgb(232, 30, 23));
        al_draw_triangle(337, 470, 302, 440, 302, 500, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(682, 470, 717, 440, 717, 500, al_map_rgb(232, 30, 23));
        al_draw_triangle(682, 470, 717, 440, 717, 500, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }

    ///EQUIPE
    if (mouse_x > 357 && mouse_x < 662 && mouse_y > 560 && mouse_y < 640) {
        al_draw_rectangle(357, 560, 662, 640, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(337, 600, 302, 570, 302, 630, al_map_rgb(232, 30, 23));
        al_draw_triangle(337, 600, 302, 570, 302, 630, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(682, 600, 717, 570, 717, 630, al_map_rgb(232, 30, 23));
        al_draw_triangle(682, 600, 717, 570, 717, 630, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }
    al_draw_text(font, al_map_rgb(232, 30, 23), 507, 320, ALLEGRO_ALIGN_CENTER, "Jouer") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 507, 450, ALLEGRO_ALIGN_CENTER, "Regles") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 507, 580, ALLEGRO_ALIGN_CENTER, "Equipe ") ;


}