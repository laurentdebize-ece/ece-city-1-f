#include "jeu.h"
#define MAPX 310
#define MAPY 100
#define CASEX_X 24


void initJeu(Jeu* jeu) {
    jeu->icone[0].width = 1024 ;
    jeu->icone[0].height = 985 ;

    jeu->icone[1].width = 512 ;
    jeu->icone[1].height = 512 ;

    jeu->icone[2].width = 288 ;
    jeu->icone[2].height = 279 ;

    jeu->icone[3].width = 321 ;
    jeu->icone[3].height = 307 ;

    jeu->icone[4].width = 309 ;
    jeu->icone[4].height = 305 ;

    jeu->time.secondes =  jeu->time.minutes = jeu->nbHabitants = jeu->mouse_x = jeu->mouse_y = jeu->nbcentrale = jeu->nbchateau = 0;
    jeu->argent= 500000;
    jeu->niveauAfficher = ROUTIER ;
    jeu->mouseIsPressed = false ;


    for(int i = 0 ; i < COLONNE ; i++) {
        for(int j = 0 ; j < LIGNE ; j++) {
            jeu->map[i][j].type = RIEN ;
            jeu->map[i][j].x = MAPX + CASEX_X*i + CASEX_X/2  ;
            jeu->map[i][j].y = MAPY + CASEX_X*j + CASEX_X/2  ;
        }
    }

}

void dessinerTerrain() {
    al_draw_rectangle(MAPX, MAPY, MAPX + 45 * CASEX_X, MAPY + 35 * CASEX_X, al_map_rgb(235, 235, 235), 1) ;
    for (int i = 0; i < 35; i++) {
        al_draw_line(MAPX, MAPY + CASEX_X * i, MAPX + 45 * CASEX_X, MAPY + CASEX_X * i, al_map_rgb(235, 235, 235), 1);
    }
    for (int i = 0; i < 45; i++) {
        al_draw_line(MAPX + CASEX_X*i, MAPY, MAPX + CASEX_X*i, MAPY + 35 * CASEX_X, al_map_rgb(235, 235, 235), 1);
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
    } else al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : %d", jeu->time.minutes,jeu->time.secondes);
    al_draw_scaled_bitmap(jeu->icone[0].image, 0, 0, 1024, 985, 900, 3, 40, 30, 0);
    al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 880, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu->nbHabitants);

    ///TOOLBOX
    al_draw_filled_rounded_rectangle(-10, 100, 205, 815, 10, 10, al_map_rgba(150, 150, 150, 150));
    al_draw_rounded_rectangle(-10, 100, 205, 815, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(-10, 99, 206, 816, 10, 10, al_map_rgb(255, 255, 255), 1);

    ///NIVEAU 0 SI PRESSEe
    if (jeu->mouse_x > 40 && jeu->mouse_x < 165 && jeu->mouse_y > 140 && jeu->mouse_y < 265) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = ROUTIER;
            al_draw_filled_rounded_rectangle(55, 155, 150, 250, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(54, 154, 151, 251, 5, 5, al_map_rgb(0, 0, 0), 5);
            al_draw_rounded_rectangle(56, 156, 149, 249, 5, 5, al_map_rgb(255, 255, 255), 3);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 103, 185, ALLEGRO_ALIGN_CENTER, "0");
        } else {
            al_draw_filled_rounded_rectangle(40, 140, 165, 265, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(41, 141, 164, 264, 5, 5, al_map_rgb(0, 0, 0), 3);
            al_draw_rounded_rectangle(40, 140, 165, 265, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(font, al_map_rgb(232, 23, 30), 103, 175, ALLEGRO_ALIGN_CENTER, "0");
        }
    } else {
        al_draw_filled_rounded_rectangle(40, 140, 165, 265, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(41, 141, 164, 264, 5, 5, al_map_rgb(0, 0, 0), 3);
        al_draw_rounded_rectangle(40, 140, 165, 265, 5, 5, al_map_rgb(255, 255, 255), 2);
        al_draw_text(font, al_map_rgb(232, 23, 30), 103, 175, ALLEGRO_ALIGN_CENTER, "0");
    }

    ///NIVEAU 1 SI PRESSEe
    if (jeu->mouse_x > 40 && jeu->mouse_x < 165 && jeu->mouse_y > 290 && jeu->mouse_y < 415) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = EAU;
            al_draw_filled_rounded_rectangle(55, 305, 150, 400, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(54, 304, 151, 401, 5, 5, al_map_rgb(0, 0, 0), 5);
            al_draw_rounded_rectangle(56, 306, 149, 399, 5, 5, al_map_rgb(255, 255, 255), 3);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 103, 335, ALLEGRO_ALIGN_CENTER, "1");
        } else {
            al_draw_filled_rounded_rectangle(40, 290, 165, 415, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(41, 291, 164, 414, 5, 5, al_map_rgb(0, 0, 0), 3);
            al_draw_rounded_rectangle(40, 290, 165, 415, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(font, al_map_rgb(232, 23, 30), 103, 325, ALLEGRO_ALIGN_CENTER, "1");
        }
    } else {
        al_draw_filled_rounded_rectangle(40, 290, 165, 415, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(41, 291, 164, 414, 5, 5, al_map_rgb(0, 0, 0), 3);
        al_draw_rounded_rectangle(40, 290, 165, 415, 5, 5, al_map_rgb(255, 255, 255), 2);
        al_draw_text(font, al_map_rgb(232, 23, 30), 103, 325, ALLEGRO_ALIGN_CENTER, "1");
    }

    ///NIVEAU 2 SI PRESSEe
    if (jeu->mouse_x > 40 && jeu->mouse_x < 165 && jeu->mouse_y > 440 && jeu->mouse_y < 565) {
        if (jeu->mouseIsPressed == true) {
            jeu->niveauAfficher = ELECTRICITE;
            al_draw_filled_rounded_rectangle(55, 455, 150, 550, 5, 5, al_map_rgb(160, 160, 160));
            al_draw_rounded_rectangle(54, 454, 151, 551, 5, 5, al_map_rgb(0, 0, 0), 4);
            al_draw_rounded_rectangle(56, 456, 149, 549, 5, 5, al_map_rgb(255, 255, 255), 2);
            al_draw_text(smallFont, al_map_rgb(232, 23, 30), 103, 485, ALLEGRO_ALIGN_CENTER, "2");
        } else {
            al_draw_filled_rounded_rectangle(40, 440, 165, 565, 5, 5, al_map_rgb(185, 185, 185));
            al_draw_rounded_rectangle(41, 441, 164, 564, 5, 5, al_map_rgb(0, 0, 0), 2);
            al_draw_rounded_rectangle(40, 440, 165, 565, 5, 5, al_map_rgb(255, 255, 255), 1);
            al_draw_text(font, al_map_rgb(232, 23, 30), 103, 475, ALLEGRO_ALIGN_CENTER, "2");
        }
    } else {
        al_draw_filled_rounded_rectangle(40, 440, 165, 565, 5, 5, al_map_rgb(210, 210, 210));
        al_draw_rounded_rectangle(41, 441, 164, 564, 5, 5, al_map_rgb(0, 0, 0), 2);
        al_draw_rounded_rectangle(40, 440, 165, 565, 5, 5, al_map_rgb(255, 255, 255), 1);
        al_draw_text(font, al_map_rgb(232, 23, 30), 103, 475, ALLEGRO_ALIGN_CENTER, "2");
    }

    al_draw_textf(smallFont, al_map_rgb(0, 0, 0), 100, 700, ALLEGRO_ALIGN_CENTER, "Niveau %d", jeu->niveauAfficher);


    ///DESSINER ICONES

    al_draw_filled_rounded_rectangle(1500, 100, 1720, 815, 10, 10, al_map_rgba(150, 150, 150, 150));
    al_draw_rounded_rectangle(1500, 100, 1720, 815, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(1500, 99, 1720, 816, 10, 10, al_map_rgb(255, 255, 255), 1);

    if (jeu->niveauAfficher == ROUTIER) {
        al_draw_scaled_bitmap(jeu->icone[1].image, 0, 0, jeu->icone[1].width, jeu->icone[1].height, 1565, 125, 85, 85,0);
        al_draw_scaled_bitmap(jeu->icone[2].image, 0, 0, jeu->icone[2].width, jeu->icone[2].height, 1558, 235, 100, 100,0);
        al_draw_scaled_bitmap(jeu->icone[3].image, 0, 0, jeu->icone[3].width, jeu->icone[3].height, 1558, 345, 100, 100,0);


        al_draw_circle(1607 , 285, 49, al_map_rgb(0, 0, 0), 4);
        al_draw_scaled_bitmap(jeu->icone[3].image, 0, 0, jeu->icone[3].width, jeu->icone[3].height, 1558, 345, 100, 100,0);
        al_draw_circle(1607, 395, 49, al_map_rgb(0, 0, 0), 4);

        if (jeu->mouseIsPressed) {
            int caseX = determinerCaseX(jeu->mouse_x) ;
            int caseY = determinerCaseY(jeu->mouse_y) ;

            if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 285) * (jeu->mouse_y - 285) < 49 * 49) {
                jeu->objetSelectionne = ROUTE;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 395) * (jeu->mouse_y - 395) <49 * 49) {
                jeu->objetSelectionne = TERRAIN;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 395) * (jeu->mouse_y - 395) <49 * 49) {
                jeu->objetSelectionne = CENTRALE;
            } else if (!(jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X)) {
                jeu->objetSelectionne = RIEN;
            } else if (jeu->objetSelectionne == ROUTE) {
                if (jeu->map[caseX][caseY].type == RIEN) {
                    jeu->map[caseX][caseY].type = ROUTE;

                }
            } else if (jeu->objetSelectionne == TERRAIN) {
                if(verifierTerrain3_3v2(&jeu, caseX, caseY) == false) {
                    al_draw_rectangle(jeu->map[caseX][caseY].x -3 * CASEX_X / 2,jeu->map[caseX][caseY].y -3*CASEX_X / 2,jeu->map[caseX][caseY].x +3 * CASEX_X / 2,jeu->map[caseX][caseY].y +3 * CASEX_X / 2,al_map_rgb(255, 0, 0), 4) ;

                }
                else if (routeProximite(&jeu, caseX,caseY) == true){
                    for(int i = 0 ; i < 3 ; i++) {
                        jeu->map[caseX-1][caseY+1-i].type = TERRAIN ;
                        jeu->map[caseX][caseY+1-i].type = TERRAIN;
                        jeu->map[caseX+1][caseY+1-i].type = TERRAIN;
                    }
                    jeu->tabhabitation[jeu->nbMaisons].x = caseX ;
                    jeu->tabhabitation[jeu->nbMaisons].y = caseY ;
                    jeu->nbMaisons ++ ;

                }
            }
            else if(jeu->objetSelectionne == CENTRALE) {
                if(verifierTerrain4_6(&jeu, caseX, caseY) == false) {
                    al_draw_rectangle(jeu->map[caseX][caseY].x -7 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -3*CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +3 * CASEX_X / 2,al_map_rgb(255, 0, 0), 4) ;

                }
            }
        }

        switch (jeu->objetSelectionne) {
            case ROUTE : {
                al_draw_circle(1607, 285, 49, al_map_rgb(255, 0, 0), 4);
                if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&
                    jeu->mouse_y < MAPY + 35 * CASEX_X) {
                    al_draw_filled_rectangle(
                            jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x - 10,
                            jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y - 10,
                            jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x + 10,
                            jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y + 10,
                            al_map_rgb(50, 50, 50));
                } else
                    al_draw_filled_rectangle(jeu->mouse_x - CASEX_X / 2, jeu->mouse_y - CASEX_X / 2,
                                             jeu->mouse_x + CASEX_X / 2, jeu->mouse_y + CASEX_X / 2,
                                             al_map_rgb(50, 50, 50));
                break;
            }
                case TERRAIN : {
                    al_draw_circle(1607, 395, 49, al_map_rgb(255, 0, 0), 4);
                    if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X) {
                        for (int i = 0; i < 3; i++) {
                                al_draw_filled_rectangle(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +CASEX_X / 2 - CASEX_X * i,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +3 * CASEX_X / 2 - CASEX_X * i, al_map_rgb(139, 69, 19));
                                al_draw_line(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +CASEX_X / 2, al_map_rgb(235, 133, 63), 1);
                                al_draw_line(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -CASEX_X / 2, al_map_rgb(235, 133, 63), 1);
                                al_draw_line(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +3 * CASEX_X / 2, al_map_rgb(235, 133, 63), 1);
                                al_draw_line(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +3 * CASEX_X / 2, al_map_rgb(235, 133, 63), 1);
                        }
                        if(verifierTerrain3_3v2(&jeu, determinerCaseX(jeu->mouse_x), determinerCaseY(jeu->mouse_y))== false ||
                                routeProximite(&jeu, determinerCaseX(jeu->mouse_x), determinerCaseY(jeu->mouse_y)) == false){
                            al_draw_filled_rectangle(jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x -3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y -3*CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].x +3 * CASEX_X / 2,jeu->map[determinerCaseX(jeu->mouse_x)][determinerCaseY(jeu->mouse_y)].y +3 * CASEX_X / 2,al_map_rgba(255, 0, 0, 50)) ;
                        }
                    }

                    break;
                }

        }
    }

    ///DESSIN DES ELEMENTS DE LA MAP
    for (int i = 0; i < COLONNE; i++) {
        for (int j = 0; j < LIGNE; j++) {
            if (jeu->map[i][j].type == ROUTE) {
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(50, 50, 50));
            }
            if (jeu->map[i][j].type == TERRAIN) {
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(139, 69, 19));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(200, 69, 19),1);

            }
            if(jeu->map[i][j].type == CABANE){
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(0, 191, 255));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(135, 206, 235),1);
            }
            if(jeu->map[i][j].type == MAISON){
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(50, 205, 50));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(34, 139, 34),1);
            }
            if (jeu->map[i][j].type == CENTRALE) {
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(240,230, 140));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(200,200,140),1);

            }
        }
    }

}

int determinerCaseX(int mouse_x) {
    int caseX ;
    caseX = mouse_x - MAPX ;
    caseX = caseX/CASEX_X ;
    return (int)caseX ;
}

int determinerCaseY(int mouse_x) {
    int caseY ;
    caseY = mouse_x - MAPY ;
    caseY = caseY/CASEX_X ;
    return (int)caseY ;
}


bool routeProximite(Jeu** jeu, int caseSourisX, int caseSourisY){
    int routeProxi = 0 ;
    for(int i=0 ; i <3; i++){
        if((*jeu)->map[caseSourisX-2][caseSourisY+1-i].type==ROUTE || (*jeu)->map[caseSourisX+2][caseSourisY+1-i].type==ROUTE){
            routeProxi++;
        }
        if((*jeu)->map[caseSourisX+1-i][caseSourisY-2].type==ROUTE || (*jeu)->map[caseSourisX+1-i][caseSourisY+2].type==ROUTE ){
            routeProxi++;
        }
    }
    if(routeProxi>=1){
        return true;
    }
    else{
        return false;
    }
}


bool verifierTerrain3_3v2(Jeu** jeu, int caseSourisX, int caseSourisY) {
    int caseLibre = 0 ;
    for(int i = 0 ; i < 3 ; i++) {
        if ((*jeu)->map[caseSourisX-1][caseSourisY+1-i].type == RIEN) {
            caseLibre++ ;
        }
        if ((*jeu)->map[caseSourisX][caseSourisY+1-i].type == RIEN) {
            caseLibre++ ;
        }
        if ((*jeu)->map[caseSourisX+1][caseSourisY+1-i].type == RIEN) {
            caseLibre++ ;
        }
    }
    if(caseLibre == 9) {
        return true ;
    }
    else return false ;
}

bool verifierTerrain4_6(Jeu** jeu, int caseSourisX, int caseSourisY) {
    int caseLibre = 0 ;
    for(int i = 0 ; i < 6 ; i++) {
        if ((*jeu)->map[caseSourisX-2][caseSourisY+2-i].type == RIEN) {
            caseLibre++ ;
        }
        if ((*jeu)->map[caseSourisX-1][caseSourisY+2-i].type == RIEN) {
            caseLibre++ ;
        }
        if ((*jeu)->map[caseSourisX][caseSourisY+2-i].type == RIEN) {
            caseLibre++ ;
        }
        if ((*jeu)->map[caseSourisX+1][caseSourisY+2-i].type == RIEN) {
            caseLibre++ ;
        }
    }
    if(caseLibre == 9) {
        return true ;
    }
    else return false ;
}
