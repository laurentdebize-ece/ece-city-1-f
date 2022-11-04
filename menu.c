#include "menu.h"


void dessinerMenu(ALLEGRO_FONT* font, int mouse_x, int mouse_y) {
    float largeur = 2;
    double color = 2.5;
    ///MENU D'AFFICHAGE
    for (int i = 0; i < 40; i++) {
        al_draw_line(422, 400 + i * largeur, 728, 400 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(422, 530 + i * largeur, 728, 530 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
        al_draw_line(422, 660 + i * largeur, 728, 660 + i * largeur,al_map_rgb(80 + color * i, 80 + color * i, 80 + color * i), largeur);
    }
    al_draw_rectangle(422, 400, 728, 480, al_map_rgb(0, 0, 0), 1.5 * largeur);
    al_draw_rectangle(422, 530, 728, 610, al_map_rgb(0, 0, 0), 1.5 * largeur);
    al_draw_rectangle(422, 660, 728, 740, al_map_rgb(0, 0, 0), 1.5 * largeur);

    ///JOUER
    if (mouse_x > 422 && mouse_x < 728 && mouse_y > 400 && mouse_y < 480) {
        al_draw_rectangle(422, 400, 728, 480, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(402, 440, 367, 410, 367, 470, al_map_rgb(232, 30, 23));
        al_draw_triangle(402, 440, 367, 410, 367, 470, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(748, 440, 783, 410, 783, 470, al_map_rgb(232, 30, 23));
        al_draw_triangle(748, 440, 783, 410, 783, 470, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }
    ///REGLES
    if (mouse_x > 422 && mouse_x < 728 && mouse_y > 530 && mouse_y < 610) {
        al_draw_rectangle(422, 530, 728, 610, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(402, 570, 367, 540, 367, 600, al_map_rgb(232, 30, 23));
        al_draw_triangle(402, 570, 367, 540, 367, 600, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(748, 570, 783, 540, 783, 600, al_map_rgb(232, 30, 23));
        al_draw_triangle(748, 570, 783, 540, 783, 600, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }

    ///EQUIPE
    if (mouse_x > 422 && mouse_x < 728 && mouse_y > 660 && mouse_y < 740) {
        al_draw_rectangle(422, 660, 728, 740, al_map_rgb(232, 30, 23), 1.5 * largeur);
        al_draw_filled_triangle(402, 700, 367, 670, 367, 730, al_map_rgb(232, 30, 23));
        al_draw_triangle(402, 700, 367, 670, 367, 730, al_map_rgb(0, 0, 0), 0.6 * largeur);

        al_draw_filled_triangle(748, 700, 783, 670, 783, 730, al_map_rgb(232, 30, 23));
        al_draw_triangle(748, 700, 783, 670, 783, 730, al_map_rgb(0, 0, 0), 0.6 * largeur);
    }
    al_draw_text(font, al_map_rgb(232, 30, 23), 575, 420, ALLEGRO_ALIGN_CENTER, "Jouer") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 575, 550, ALLEGRO_ALIGN_CENTER, "Regles") ;
    al_draw_text(font, al_map_rgb(232, 30, 23), 575, 680, ALLEGRO_ALIGN_CENTER, "Equipe ") ;
}

void dessinerEquipe(Menu* menu, ALLEGRO_FONT* font, float width, float height, float mouse_x, float mouse_y) {
    float largeur = 4;
    double color = 2;
    al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150)) ;

    if ( mouse_x < 170 && mouse_x > 10 && mouse_y < 70 && mouse_y > 10) {
        al_draw_filled_rectangle(10, 10, 170, 70, al_map_rgb(200,200,200)) ;
    }
    else   al_draw_filled_rectangle(10, 10, 170, 70, al_map_rgb(150,150,150)) ;
    al_draw_rectangle(10, 10, 170, 70, al_map_rgb(10,10, 10), 2);
    al_draw_text(font, al_map_rgb(10, 10, 10), 90, 20, ALLEGRO_ALIGN_CENTER, "Retour") ;

    for (int i = 0; i < 70; i++) {
        al_draw_line(200, 200 + i * largeur, 950, 200 + i * largeur,al_map_rgba(255,20 + color*i,color * i, 100), largeur);
        al_draw_line(200, 480 + i * largeur, 950, 480 + i * largeur,al_map_rgba(255,160 - color*i,140- color * i, 50), largeur);
    }

    al_draw_scaled_bitmap(menu->batimentDeco[6], 0, 0, 307, 305, 272, 300, 282/2, 321/2, 0) ;
    al_draw_scaled_bitmap(menu->batimentDeco[7], 0, 0, 330, 322, 717, 560, 282/2, 321/2, 0) ;

    al_draw_scaled_bitmap(menu->batimentDeco[2], 0, 0, 360, 1000, 110, 285, 3*360/7, 1000/2, 0) ;
    al_draw_scaled_bitmap(menu->batimentDeco[3], 0, 0, 300, 1115, 890, 220, 300/2, 1115/2, 1) ;



    al_draw_text(font, al_map_rgb(0, 0, 0), 343, 240, ALLEGRO_ALIGN_CENTER, "Fares") ;
    al_draw_text(font, al_map_rgb(0, 0, 0), 788, 240, ALLEGRO_ALIGN_CENTER, "Lisa") ;
    al_draw_text(font, al_map_rgb(0, 0, 0), 343, 500, ALLEGRO_ALIGN_CENTER, "Eva") ;
    al_draw_text(font, al_map_rgb(0, 0, 0), 788, 500, ALLEGRO_ALIGN_CENTER, "Valentin") ;

}
