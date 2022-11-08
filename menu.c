#include "menu.h"


void initBitmapDeco(Menu* menu) {
    menu->deco[0].width = 360 ;
    menu->deco[0].height = 1000 ;

    menu->deco[1].width = 300 ;
    menu->deco[1].height = 1115 ;

    menu->deco[2].width = 307 ;
    menu->deco[2].height = 305 ;

    menu->deco[3].width = 330 ;
    menu->deco[3].height = 322 ;

    menu->deco[4].width = 1024 ;
    menu->deco[4].height = 767 ;
}

void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) {
    float largeur = 2;
    double color = 2.5;
    ///MENU D'AFFICHAGE
    for (int i = 0; i < 40; i++) {
        al_draw_line(357, 300 + i * largeur, 662, 300 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(357, 430 + i * largeur, 662, 430 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(357, 560 + i * largeur, 662, 560 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
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

void dessinerEquipe(Menu* menu, ALLEGRO_FONT* font, float width, float height, float mouse_x, float mouse_y) {
    float largeur = 4;
    double color = 2;
    al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150));

    if (mouse_x < 170 && mouse_x > 10 && mouse_y < 70 && mouse_y > 10) {
        al_draw_filled_rectangle(10, 10, 170, 70, al_map_rgb(200, 200, 200));
    } else al_draw_filled_rectangle(10, 10, 170, 70, al_map_rgb(150, 150, 150));
    al_draw_rectangle(10, 10, 170, 70, al_map_rgb(10, 10, 10), 2);
    al_draw_text(font, al_map_rgb(10, 10, 10), 90, 20, ALLEGRO_ALIGN_CENTER, "Retour");

    for (int i = 0; i < 70; i++) {
        al_draw_line(157, 100 + i * largeur, 862, 100 + i * largeur, al_map_rgba(255, 20 + color * i, color * i, 100),
                     largeur);
        al_draw_line(157, 380 + i * largeur, 862, 380 + i * largeur,
                     al_map_rgba(255, 160 - color * i, 140 - color * i, 50), largeur);
    }

    al_draw_scaled_bitmap(menu->deco[2].image, 0, 0, menu->deco[2].width, menu->deco[2].height, 230, 200, 282 / 2, 321 / 2, 0);
    al_draw_scaled_bitmap(menu->deco[3].image, 0, 0, menu->deco[3].width, menu->deco[3].height, 630, 460, 282 / 2, 321 / 2, 0);

    al_draw_scaled_bitmap(menu->deco[0].image, 0, 0, menu->deco[0].width, menu->deco[0].height, 80, 275, 3 * 360 / 7, 3 * 1000 / 7, 0);
    al_draw_scaled_bitmap(menu->deco[1].image, 0, 0, menu->deco[1].width, menu->deco[1].height, 800, 230, 3 * 300 / 7, 3 * 1115 / 7, 1);

    al_draw_text(font, al_map_rgb(0, 0, 0), 300, 140, ALLEGRO_ALIGN_CENTER, "Fares");
    al_draw_text(font, al_map_rgb(0, 0, 0), 700, 140, ALLEGRO_ALIGN_CENTER, "Lisa");
    al_draw_text(font, al_map_rgb(0, 0, 0), 300, 400, ALLEGRO_ALIGN_CENTER, "Eva");
    al_draw_text(font, al_map_rgb(0, 0, 0), 700, 400, ALLEGRO_ALIGN_CENTER, "Valentin");
}
