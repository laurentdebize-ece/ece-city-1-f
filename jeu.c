#include "jeu.h"

void initJeu(Jeu* jeu) {
    jeu->time.secondes = 0 ;
    jeu->time.minutes = 0 ;
    jeu->nbHabitants = 0;
}

void temps(Temps* time, int compteur) {
    if(compteur%50 == 0){
        time->secondes++ ;
    }
    if(time->secondes == 60) {
        time->minutes++ ;
        time->secondes = 0 ;
    }
}

void dessinerJeu(ALLEGRO_FONT* font, Jeu* jeu) {
    dessinerTerrain() ;
    al_draw_filled_rectangle(0, 720, jeu->width, 768, al_map_rgb(30, 144, 255)) ;
    if(jeu->time.secondes < 10) {
        al_draw_textf(font, al_map_rgb(235, 235, 235), 990,7, ALLEGRO_ALIGN_CENTER, "%d : 0%d",jeu->time.minutes, jeu->time.secondes);
    }
    else al_draw_textf(font, al_map_rgb(235, 235, 235), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : %d",jeu->time.minutes, jeu->time.secondes);
    al_draw_scaled_bitmap(jeu->bitmap[1], 0, 0, 1024, 985, 900, 3, 40, 30, 0) ;
    al_draw_textf(font, al_map_rgb(255, 255, 255), 880, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu->nbHabitants) ;

    ///TOOLBOX
    al_draw_filled_rounded_rectangle(-10, 5, 105, 715, 10, 10, al_map_rgba(150, 150, 150, 150)) ;
    al_draw_rounded_rectangle(-10, 5, 105, 715, 10, 10, al_map_rgb(0, 0, 0), 3) ;
    al_draw_rounded_rectangle(-10, 4, 106, 716, 10, 10, al_map_rgb(255, 255, 255), 1) ;

    ///NIVEAU 0
    al_draw_filled_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(210, 210, 210)) ;
    al_draw_rounded_rectangle(6, 16, 94, 99, 5, 5, al_map_rgb(0, 0, 0), 2) ;
    al_draw_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(255, 255, 255), 1) ;

    ///NIVEAU 1
    al_draw_filled_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(210, 210, 210)) ;
    al_draw_rounded_rectangle(6, 111, 94, 194, 5, 5, al_map_rgb(0, 0, 0), 2) ;
    al_draw_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(255, 255, 255), 1) ;

    ///NIVEAU 2
    al_draw_filled_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(210, 210, 210)) ;
    al_draw_rounded_rectangle(6, 206, 94, 289, 5, 5, al_map_rgb(0, 0, 0), 2) ;
    al_draw_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(255, 255, 255), 1) ;



}

void dessinerTerrain() {
    al_draw_rectangle(120, 6, 1020, 706, al_map_rgb(235, 235, 235), 1) ;
    for (int i = 0; i < 35; i++) {
        al_draw_line(120, 6 + 20 * i, 1020, 6 + 20 * i, al_map_rgb(235, 235, 235), 1);
    }
    for (int i = 0; i < 45; i++) {
        al_draw_line(120 + 20*i, 6, 120 + 20*i, 706, al_map_rgb(235, 235, 235), 1);
    }
}