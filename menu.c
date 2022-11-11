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
    for (int i = 0; i < 60; i++) {
        al_draw_line(650, 400 + i * largeur, 1050, 400 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(650, 580 + i * largeur, 1050, 580 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(650, 760 + i * largeur, 1050, 760 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
    }
    al_draw_rectangle(650, 400, 1050, 520, al_map_rgb(0, 0, 0), 2 * largeur);
    al_draw_rectangle(650, 580, 1050, 700, al_map_rgb(0, 0, 0), 2 * largeur);
    al_draw_rectangle(650, 760, 1050, 880, al_map_rgb(0, 0, 0), 2 * largeur);

    ///JOUER
    if (mouse_x > 650 && mouse_x < 1050 && mouse_y > 400 && mouse_y < 520) {
        al_draw_rectangle(650, 400, 1050, 520, al_map_rgb(232, 30, 23), 2 * largeur);
        al_draw_filled_triangle(610, 460, 560, 410, 560, 510, al_map_rgb(232, 30, 23));
        al_draw_triangle(610, 460, 560, 410, 560, 510, al_map_rgb(0, 0, 0), largeur);

        al_draw_filled_triangle(1090, 460, 1140, 410, 1140, 510, al_map_rgb(232, 30, 23));
        al_draw_triangle(1090, 460, 1140, 410, 1140, 510, al_map_rgb(0, 0, 0), largeur);
    }
    ///REGLES
    if (mouse_x > 650 && mouse_x < 1050 && mouse_y > 580 && mouse_y < 700) {
        al_draw_rectangle(650, 580, 1050, 700, al_map_rgb(232, 30, 23), 2 * largeur);
        al_draw_filled_triangle(610, 640, 560, 590, 560, 690, al_map_rgb(232, 30, 23));
        al_draw_triangle(610, 640, 560, 590, 560, 690, al_map_rgb(0, 0, 0), largeur);

        al_draw_filled_triangle(1090, 640, 1140, 590, 1140, 690, al_map_rgb(232, 30, 23));
        al_draw_triangle(1090, 640, 1140, 590, 1140, 690, al_map_rgb(0, 0, 0), largeur);

    }
    ///EQUIPE
    if (mouse_x > 650 && mouse_x < 1050 && mouse_y > 760 && mouse_y < 880) {
        al_draw_rectangle(650, 760, 1050, 880, al_map_rgb(232, 30, 23), 2 * largeur);
        al_draw_filled_triangle(610, 820, 560, 770, 560, 870, al_map_rgb(232, 30, 23));
        al_draw_triangle(610, 820, 560, 770, 560, 870, al_map_rgb(0, 0, 0), largeur);

        al_draw_filled_triangle(1090, 820, 1140, 770, 1140, 870, al_map_rgb(232, 30, 23));
        al_draw_triangle(1090, 820, 1140, 770, 1140, 870, al_map_rgb(0, 0, 0), largeur);
    }
    al_draw_text(font, al_map_rgb(232, 30, 23), 850, 430, ALLEGRO_ALIGN_CENTER, "Jouer") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 850, 610, ALLEGRO_ALIGN_CENTER, "Regles") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 850, 790, ALLEGRO_ALIGN_CENTER, "Equipe") ;
}

void dessinerEquipe(Menu* menu, ALLEGRO_FONT* font, float width, float height, float mouse_x, float mouse_y) {
    float largeur = 4;
    double color = 1.5;
    al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150));

    if (mouse_x < 300 && mouse_x > 20 && mouse_y < 90 && mouse_y > 20) {
        al_draw_filled_rectangle(20, 20, 300, 90, al_map_rgb(200, 200, 200));
    } else al_draw_filled_rectangle(20, 20, 300, 90, al_map_rgb(150, 150, 150));
    al_draw_rectangle(20, 20, 300, 90, al_map_rgb(10, 10, 10), 2);
    al_draw_text(font, al_map_rgb(10, 10, 10), 155, 25, ALLEGRO_ALIGN_CENTER, "Retour");

    for (int i = 0; i < 80; i++) {
        al_draw_line(260, 200 + i * largeur, 1440, 200 + i * largeur, al_map_rgba(255, 40 + color * i, 20+color * i, 100),largeur);
        al_draw_line(260, 520 + i * largeur, 1440, 520+ i * largeur,al_map_rgba(255, 160 - color * i, 140 - color * i, 50), largeur);
    }


    al_draw_scaled_bitmap(menu->deco[2].image, 0, 0, menu->deco[2].width, menu->deco[2].height, 406, 300, 2*282 /3, 4*341 / 7, 0);
    al_draw_scaled_bitmap(menu->deco[3].image, 0, 0, menu->deco[3].width, menu->deco[3].height, 1006, 610, 2*282 /3, 4*341 /7, 0);

    al_draw_scaled_bitmap(menu->deco[0].image, 0, 0, menu->deco[0].width, menu->deco[0].height, 160, 260, 3* menu->deco[0].width / 5, 3 * menu->deco[0].height /5, 0);
    al_draw_scaled_bitmap(menu->deco[1].image, 0, 0, menu->deco[1].width, menu->deco[1].height, 1370, 200, 3 * menu->deco[1].width / 5, 3 * menu->deco[1].height /5, 1);

    al_draw_text(font, al_map_rgb(0, 0, 0), 500, 230, ALLEGRO_ALIGN_CENTER, "Fares");
    al_draw_text(font, al_map_rgb(0, 0, 0), 1100, 230, ALLEGRO_ALIGN_CENTER, "Lisa");
    al_draw_text(font, al_map_rgb(0, 0, 0), 500, 530, ALLEGRO_ALIGN_CENTER, "Eva");
    al_draw_text(font, al_map_rgb(0, 0, 0), 1100, 530, ALLEGRO_ALIGN_CENTER, "Valentin");
}
