#include "jeu.h"

void initJeu(Jeu* jeu) {
    jeu->icone[0].width = 1024 ;
    jeu->icone[0].height = 985 ;

    jeu->icone[1].width = 512 ;
    jeu->icone[1].height = 512 ;

    jeu->icone[2].width = 288 ;
    jeu->icone[2].height = 279 ;

    jeu->time.secondes =  jeu->time.minutes = jeu->nbHabitants = jeu->mouse_x = jeu->mouse_y = jeu->nbcentrale = jeu->nbchateau = 0;
    jeu->argent= 500000;
    jeu->niveauAfficher = ROUTIER ;
    jeu->mouseIsPressed = false ;


    for(int i = 0 ; i < COLONNE ; i++) {
        for(int j = 0 ; j < LIGNE ; j++) {
            jeu->map[i][j].type = RIEN ;
            jeu->map[i][j].x = 130 + 20*i ;
            jeu->map[i][j].y = 16 + 20*j ;
        }
    }

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

void temps(Temps* time, int compteur) {
    if(compteur%50 == 0){
        time->secondes++ ;
    }
    if(time->secondes == 60) {
        time->minutes++ ;
        time->secondes = 0 ;
    }
}

void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) {
    dessinerTerrain();


    //al_draw_filled_rectangle(0, 720, jeu->width, 768, al_map_rgb(30, 144, 255));

    ///TIMER
    if (jeu->time.secondes < 10) {
        al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 990, 725, ALLEGRO_ALIGN_CENTER, "%d : 0%d",
                      jeu->time.minutes, jeu->time.secondes);
    } else
        al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : %d", jeu->time.minutes,
                      jeu->time.secondes);
    al_draw_scaled_bitmap(jeu->icone[0].image, 0, 0, 1024, 985, 900, 3, 40, 30, 0);
    al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 880, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu->nbHabitants);

    ///TOOLBOX
    al_draw_filled_rounded_rectangle(-10, 5, 105, 715, 10, 10, al_map_rgba(150, 150, 150, 150));
    al_draw_rounded_rectangle(-10, 5, 105, 715, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(-10, 4, 106, 716, 10, 10, al_map_rgb(255, 255, 255), 1);

    ///NIVEAU 0 SI PRESSEe
    if (jeu->mouse_x > 5 && jeu->mouse_x < 95 && jeu->mouse_y > 15 && jeu->mouse_y < 100) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = ROUTIER ;
            al_draw_filled_rounded_rectangle(12, 22, 88, 92, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(11, 21, 89, 93, 5, 5, al_map_rgb(0, 0, 0), 4);
            al_draw_rounded_rectangle(13, 23, 87, 91, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 50, 45, ALLEGRO_ALIGN_CENTER, "0");
        }
        else {
            al_draw_filled_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(6, 16, 94, 99, 5, 5, al_map_rgb(0, 0, 0), 2);
            al_draw_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(255, 255, 255), 1);
            al_draw_text(font, al_map_rgb(232, 23, 30), 50, 35, ALLEGRO_ALIGN_CENTER, "0");
        }
    }
    else {
        al_draw_filled_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(6, 16, 94, 99, 5, 5, al_map_rgb(0, 0, 0), 2);
        al_draw_rounded_rectangle(5, 15, 95, 100, 5, 5, al_map_rgb(255, 255, 255), 1);
        al_draw_text(font, al_map_rgb(232, 23, 30), 50, 35, ALLEGRO_ALIGN_CENTER, "0");
    }

    ///NIVEAU 1 SI PRESSEe
    if (jeu->mouse_x > 5 && jeu->mouse_x < 95 && jeu->mouse_y > 110 && jeu->mouse_y < 195) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = EAU ;
            al_draw_filled_rounded_rectangle(12, 117, 88, 188, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(11, 116, 89, 189, 5, 5, al_map_rgb(0, 0, 0), 4);
            al_draw_rounded_rectangle(13, 118, 87, 187, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 50, 140, ALLEGRO_ALIGN_CENTER, "1");
        }
        else {
            al_draw_filled_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(6, 111, 94, 194, 5, 5, al_map_rgb(0, 0, 0), 2);
            al_draw_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(255, 255, 255), 1);
            al_draw_text(font, al_map_rgb(232, 23, 30), 50, 130, ALLEGRO_ALIGN_CENTER, "1");
        }
    }
    else {
        al_draw_filled_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(6, 111, 94, 194, 5, 5, al_map_rgb(0, 0, 0), 2);
        al_draw_rounded_rectangle(5, 110, 95, 195, 5, 5, al_map_rgb(255, 255, 255), 1);
        al_draw_text(font, al_map_rgb(232, 23, 30), 50, 130, ALLEGRO_ALIGN_CENTER, "1");
    }

    ///NIVEAU 2 SI PRESSEe
    if (jeu->mouse_x > 5 && jeu->mouse_x < 95 && jeu->mouse_y > 205 && jeu->mouse_y < 290) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = ELECTRICITE ;
            al_draw_filled_rounded_rectangle(12, 212, 88, 283, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(11, 211, 89, 284, 5, 5, al_map_rgb(0, 0, 0), 4);
            al_draw_rounded_rectangle(13, 213, 87, 282, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 50, 240, ALLEGRO_ALIGN_CENTER, "2");
        }
        else {
            al_draw_filled_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(6, 206, 94, 289, 5, 5, al_map_rgb(0, 0, 0), 2);
            al_draw_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(255, 255, 255), 1);
            al_draw_text(font, al_map_rgb(232, 23, 30), 50, 230, ALLEGRO_ALIGN_CENTER, "2");
        }
    }
    else {
        al_draw_filled_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(6, 206, 94, 289, 5, 5, al_map_rgb(0, 0, 0), 2);
        al_draw_rounded_rectangle(5, 205, 95, 290, 5, 5, al_map_rgb(255, 255, 255), 1);
        al_draw_text(font, al_map_rgb(232, 23, 30), 50, 230, ALLEGRO_ALIGN_CENTER, "2");
    }

    ///DESSINER ICONES
    if(jeu->niveauAfficher == ROUTIER) {
        al_draw_scaled_bitmap(jeu->icone[1].image, 0, 0, jeu->icone[1].width,jeu->icone[1].height, 30, 300, 40, 40, 0) ;
        al_draw_scaled_bitmap(jeu->icone[2].image, 0, 0,jeu->icone[2].width, jeu->icone[2].height, 7, 345, 85, 85, 0) ;
        al_draw_circle(49.5, 387.5, 85/2, al_map_rgb(0, 0, 0), 3) ;
        if(jeu->mouseIsPressed) {
            if ((jeu->mouse_x - 49.5) * (jeu->mouse_x - 49.5) + (jeu->mouse_y - 387.5) * (jeu->mouse_y - 387.5) <
                42.5 * 42.5) {
                jeu->objetSelectionne = ROUTE;
            }
            else if(!(jeu->mouse_x > 120 && jeu->mouse_x < 1020 && jeu->mouse_y > 6 && jeu->mouse_y < 706)){
                jeu->objetSelectionne = RIEN ;
            }
            else if(jeu->objetSelectionne == ROUTE){
                if(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].type == RIEN) {
                    jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].type = ROUTE ;
                }
            }


        }
        switch (jeu->objetSelectionne) {
            case ROUTE : {
                al_draw_circle(49.5, 387.5, 85/2, al_map_rgb(255, 0, 0), 3) ;
                al_draw_filled_rectangle(jeu->mouse_x-10, jeu->mouse_y-10, jeu->mouse_x+10, jeu->mouse_y+10, al_map_rgb(50, 50, 50)) ;
                break ;
            }

        }
    }

    ///DESSIN DES ELEMENTS DE LA MAP
    for(int i = 0 ; i < COLONNE ; i++) {
        for(int j = 0 ; j < LIGNE ; j++) {
            if(jeu->map[i][j].type == ROUTE) {
                al_draw_filled_rectangle(jeu->map[i][j].x-10, jeu->map[i][j].y-10, jeu->map[i][j].x+10, jeu->map[i][j].y+10, al_map_rgb(50, 50, 50)) ;
            }
        }
    }

}

int determinerCaseX(int mouse_x) {
    int caseX = 0 ;
    caseX = mouse_x - 120 ;
    caseX = caseX/20 ;
    return (int)caseX ;
}

int determinerCaseY(int mouse_x) {
    int caseY = 0 ;
    caseY = mouse_x - 6 ;
    caseY = caseY/20 ;
    return (int)caseY ;
}

void mettreCentrale(){



}