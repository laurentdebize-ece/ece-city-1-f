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

void dessinerJeu(ALLEGRO_FONT* font, Jeu jeu, float width, float height) {
    al_draw_filled_rectangle(0, 0, width, 35, al_map_rgba(150, 150, 150, 200)) ;
    if(jeu.time.secondes < 10) {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 1110,7, ALLEGRO_ALIGN_CENTER, "%d : 0%d",jeu.time.minutes, jeu.time.secondes);
    }
    else al_draw_textf(font, al_map_rgb(255, 255, 255), 1110, 7, ALLEGRO_ALIGN_CENTER, "%d : %d",jeu.time.minutes, jeu.time.secondes);

}