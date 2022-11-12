#include "jeu.h"
#define MAPX 290
#define MAPY 75
#define CASEX_X (float)45
#define ARGENTDEP 500000


void initJeu(Jeu* jeu) {
    for(int i = 0 ; i<4 ;i++) {
        jeu->route[i].width = 25 ;
        jeu->route[i].height = 25 ;
    }

    jeu->habitations[TERRAIN].width = 75 ;
    jeu->habitations[TERRAIN].height = 75 ;

    jeu->habitations[CABANE].width = 112 ;
    jeu->habitations[CABANE].height = 147 ;

    jeu->habitations[MAISON].width = 112 ;
    jeu->habitations[MAISON].height = 160 ;

    jeu->habitations[IMMEUBLE].width = 439 ;
    jeu->habitations[IMMEUBLE].height = 468 ;

    jeu->habitations[GRATTE_CIEL].width = 134 ;
    jeu->habitations[GRATTE_CIEL].height = 342 ;

    jeu->habitations[CONSTRUCTION].width = 129 ;
    jeu->habitations[CONSTRUCTION].height = 112 ;


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

    jeu->icone[5].width = 320 ;
    jeu->icone[5].height = 305 ;

    jeu->time[0].secondes =  jeu->time[0].minutes = jeu->nbHabitants = jeu->mouse_x = jeu->mouse_y = jeu->nbCentrale = jeu->nbChateau = 0;
    jeu->argent= ARGENTDEP;
    jeu->niveauAfficher = ROUTIER ;
    jeu->mouseIsPressed = false ;
    jeu->objetSelectionne = RIEN ;



    for(int i = 0 ; i < COLONNE ; i++) {
        for(int j = 0 ; j < LIGNE ; j++) {
            jeu->map[i][j].type = RIEN ;
            jeu->map[i][j].x = MAPX + CASEX_X*i + CASEX_X/2  ;
            jeu->map[i][j].y = MAPY + CASEX_X*j + CASEX_X/2  ;
            for(int k = 0 ; k < 4 ; k++) {
                jeu->map[i][j].route[k] = 0 ;
            }
            jeu->map[i][j].rotation = 0 ;
        }
    }
    for(int i = 0 ; i < MAX ; i++){
        jeu->tabHabitations[i].evolution = 0 ;
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

void temps(Temps* time, int compteur, int numTimer) {
    if(compteur%50 == 0){
        time->secondes++ ;
    }
    if(time->secondes == 60 && numTimer == 0) {
        time->minutes++ ;
        time->secondes = 0 ;
    }
}

void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) {
    ///CASE SUR LAQUELLE SE TROUVE LA SOURIS
    int caseX = determinerCaseX(jeu->mouse_x);
    int caseY = determinerCaseY(jeu->mouse_y);

    /// CORDONNEES (x,y) DE LA CASE (X,Y)
    float x_CaseXY = jeu->map[caseX][caseY].x;
    float y_CaseXY = jeu->map[caseX][caseY].y;

    ///RAPPORT TAILLE CASE ACTUELLE ET TAILLE ORIGINAL (pour zoomer si on le fait plus tard)
    float scale = CASEX_X/25 ;

    dessinerTerrain();

    ///TIMER
    if (jeu->time[0].secondes < 10) {
        al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : 0%d",
                      jeu->time[0].minutes, jeu->time[0].secondes);
    } else
        al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : %d", jeu->time[0].minutes,
                      jeu->time[0].secondes);
    ///DESSINER NB HABITANT
    al_draw_scaled_bitmap(jeu->icone[0].image, 0, 0, 1024, 985, 900, 3, 40, 30, 0);
    al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 880, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu->nbHabitants);
    al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 100, 7, ALLEGRO_ALIGN_CENTER, "ELEC : %d", jeu->capaciteElec);
    ///DESSINER ARGENT
    al_draw_textf(smallFont, al_map_rgb(47, 58, 124), 700, 7, ALLEGRO_ALIGN_CENTER, "TIMER : %d", jeu->argent);


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

    /// NIVEAU 2 SI PRESSEe
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


    ///DESSINER PARTIE CONSTRUCTION
    al_draw_filled_rounded_rectangle(1500, 100, 1720, 815, 10, 10, al_map_rgba(150, 150, 150, 150));
    al_draw_rounded_rectangle(1500, 100, 1720, 815, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(1500, 99, 1720, 816, 10, 10, al_map_rgb(255, 255, 255), 1);


    ///////////AFFICHAGE DU NIVEAU O ///////////////

    if (jeu->niveauAfficher == ROUTIER) {
        //Dessiner les icones des batiments
        al_draw_scaled_bitmap(jeu->icone[1].image, 0, 0, jeu->icone[1].width, jeu->icone[1].height, 1565, 125, 85, 85,
                              0);

        al_draw_scaled_bitmap(jeu->icone[2].image, 0, 0, jeu->icone[2].width, jeu->icone[2].height, 1558, 235, 100, 100,
                              0);
        al_draw_circle(1607, 285, 49, al_map_rgb(0, 0, 0), 4);

        al_draw_scaled_bitmap(jeu->icone[3].image, 0, 0, jeu->icone[3].width, jeu->icone[3].height, 1558, 345, 100, 100,
                              0);
        al_draw_circle(1607, 395, 49, al_map_rgb(0, 0, 0), 4);

        al_draw_scaled_bitmap(jeu->icone[4].image, 0, 0, jeu->icone[4].width, jeu->icone[4].height, 1558, 455, 100, 100,
                              0);
        al_draw_circle(1607, 505, 49, al_map_rgb(0, 0, 0), 4);

        al_draw_scaled_bitmap(jeu->icone[5].image, 0, 0, jeu->icone[5].width, jeu->icone[5].height, 1558, 565, 100, 100,
                              0);
        al_draw_circle(1607, 615, 49, al_map_rgb(0, 0, 0), 4);


        ///ON SELECTIONNE UN OBJET
        switch (jeu->objetSelectionne) {
            case ROUTE : {
                al_draw_circle(1607, 285, 49, al_map_rgb(255, 0, 0), 4);
                //Si on est dans la grille du jeu, il dessine le carré dans la bonne case
                if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&
                    jeu->mouse_y < MAPY + 35 * CASEX_X) {
                    al_draw_filled_rectangle(x_CaseXY - 10, y_CaseXY - 10, x_CaseXY + 10, y_CaseXY + 10,
                                             al_map_rgb(50, 50, 50));
                } else
                    al_draw_filled_rectangle(jeu->mouse_x - CASEX_X / 2, jeu->mouse_y - CASEX_X / 2,
                                             jeu->mouse_x + CASEX_X / 2, jeu->mouse_y + CASEX_X / 2,
                                             al_map_rgb(50, 50, 50));
                break;
            }
            case TERRAIN : {
                al_draw_circle(1607, 395, 49, al_map_rgb(255, 0, 0), 4);
                //Si on est dans la grille du jeu, il dessine le carré dans les bonnes cases
                if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X) {
                    al_draw_scaled_bitmap(jeu->habitations[TERRAIN].image, 0, 0, jeu->habitations[TERRAIN].width, jeu->habitations[TERRAIN].height, x_CaseXY - 3*CASEX_X/2, y_CaseXY - 3*CASEX_X/2, 3*CASEX_X, 3*CASEX_X, 0) ;
                    // Si les conditions ne sont pas vérifiés, on affiche le batiments en rouge
                    if (verifierTerrain3_3v2(&jeu, caseX, caseY) == false ||routeProximiteMaison(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 3 * CASEX_X / 2, y_CaseXY - 3 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 3 * CASEX_X / 2,al_map_rgba(255, 0, 0, 50));
                    }
                }
                break;
            }
            case CHATEAU : {
                al_draw_circle(1607, 505, 49, al_map_rgb(255, 0, 0), 4);
                if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X) {
                    al_draw_filled_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgb(240, 230, 140));
                    if (verifierTerrain4_6(&jeu, caseX, caseY) == false ||routeProximiteCentrale(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgba(255, 0, 0, 150));
                    }

                }
                break;
            }
            case CENTRALE : {
                al_draw_circle(1607, 615, 49, al_map_rgb(255, 0, 0), 4);
                if (jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X) {
                    al_draw_filled_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgb(255, 140, 0));
                    if (verifierTerrain4_6(&jeu, caseX, caseY) == false ||routeProximiteCentrale(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgba(255, 0, 0, 150));
                    }

                }
                break;
            }
        }


        ///QUAND ON APPUIE SUR LE BOUTON DE LA SOURIS
        if (jeu->mouseIsPressed) {
            //Quand on appuie sur les icones des batiments, on selectionne un objet
            if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 285) * (jeu->mouse_y - 285) < 49 * 49) {
                jeu->objetSelectionne = ROUTE;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 395) * (jeu->mouse_y - 395) <
                       49 * 49) {
                jeu->objetSelectionne = TERRAIN;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 505) * (jeu->mouse_y - 505) <
                       49 * 49) {
                jeu->objetSelectionne = CHATEAU;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 615) * (jeu->mouse_y - 615) <
                       49 * 49) {
                jeu->objetSelectionne = CENTRALE;
            }
                //Si on n'appuie ni sur les icones, ni sur la grille, on enleve la sélection
            else if (!(jeu->mouse_x > MAPX && jeu->mouse_x < MAPX + 45 * CASEX_X && jeu->mouse_y > MAPY &&jeu->mouse_y < MAPY + 35 * CASEX_X)) {
                jeu->objetSelectionne = RIEN;
            }
                //A ce stade la de la condition, on est forcement dans la grille, donc on est logiquement en train de poser les batiments
                //Ducoup on vérifie chaque batiments tour à tour
            else {
                switch (jeu->objetSelectionne) {
                    case ROUTE : {
                        if (jeu->map[caseX][caseY].type == RIEN && jeu->argent >= 10) {
                            jeu->map[caseX][caseY].type = ROUTE;
                            jeu->argent -= 10;
                        }
                        break;
                    }
                    case TERRAIN : {
                        //On peut pas poser le terrain, on le surbrille en rouge
                        if (verifierTerrain3_3v2(&jeu, caseX, caseY) == false) {
                            al_draw_rectangle(x_CaseXY - 3 * CASEX_X / 2, y_CaseXY - 3 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 3 * CASEX_X / 2,al_map_rgb(255, 0, 0), 4);

                        }
                        //On peut poser le terrain (pas de batiments déjà posé ici), on vérifie maintenant la proximité à une route
                        else if (routeProximiteMaison(&jeu, caseX, caseY) == true && jeu->argent >= 1000) {
                            jeu->argent -= 1000;
                            //On change les données de notre tab 2D
                            for (int i = 0; i < 3; i++) {
                                jeu->map[caseX - 1][caseY + 1 - i].type = TERRAIN;
                                jeu->map[caseX][caseY + 1 - i].type = TERRAIN;
                                jeu->map[caseX + 1][caseY + 1 - i].type = TERRAIN;
                            }
                            //On note la Case dans le tab des Habitations
                            jeu->tabHabitations[jeu->nbMaisons].caseX = caseX;
                            jeu->tabHabitations[jeu->nbMaisons].caseY = caseY;
                            jeu->tabHabitations[jeu->nbMaisons].tempsEvolution = jeu->time[1].secondes;
                            jeu->nbMaisons++;
                            ///POSE DU TERRAIN + CREATION DANS LE TAB

                        }
                        break;
                    }
                    case CHATEAU : {
                        //Si on peut pas poser le terrain, on le surbrille en rouge
                        if (verifierTerrain4_6(&jeu, caseX, caseY) == false) {
                            al_draw_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgb(255, 0, 0), 4);
                        }
                            //Sinon on peut le poser, on verifie donc les routes à cotés
                        else if (routeProximiteCentrale(&jeu, caseX, caseY) == true && jeu->argent >= 100000) {
                            jeu->argent -= 100000;
                            for (int i = 0; i < 6; i++) {
                                jeu->map[caseX - 2][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX - 1][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX + 1][caseY + 2 - i].type = CHATEAU;
                            }
                            jeu->tabChateau[jeu->nbChateau].x = caseX;
                            jeu->tabChateau[jeu->nbChateau].y = caseY;
                            jeu->nbChateau++;
                            jeu->capaciteEau += 5000;
                        }
                        break;
                    }
                    case CENTRALE : {
                        //PAREIL QUE LE CHATEAU D'EAU
                        if (verifierTerrain4_6(&jeu, caseX, caseY) == false) {
                            al_draw_rectangle(x_CaseXY - 5 * CASEX_X / 2, y_CaseXY - 7 * CASEX_X / 2,x_CaseXY + 3 * CASEX_X / 2, y_CaseXY + 5 * CASEX_X / 2,al_map_rgb(255, 0, 0), 4);
                        }
                        else if (routeProximiteCentrale(&jeu, caseX, caseY) == true && jeu->argent >= 100000) {
                            jeu->argent -= 100000;
                            for (int i = 0; i < 6; i++) {
                                jeu->map[caseX - 2][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX - 1][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX + 1][caseY + 2 - i].type = CENTRALE;
                            }
                            jeu->tabCentrale[jeu->nbCentrale].x = caseX;
                            jeu->tabCentrale[jeu->nbCentrale].y = caseY;
                            jeu->nbCentrale++;
                            jeu->capaciteElec += 5000;
                        }
                        break;
                    }
                }
            }
        }
    }



    ///DESSIN DES ELEMENTS DE LA MAP
    for (int j = 0; j < LIGNE; j++) {
        for (int i = 0; i < COLONNE; i++) {
            //placement des routes
            if (jeu->map[i][j].type == ROUTE) {
                verifierAffichageRoute(&jeu, i, j) ;
                int quelRoute = combinaison(*jeu, i, j, &jeu->map[i][j].rotation) ;
                al_draw_scaled_rotated_bitmap(jeu->route[quelRoute].image, 12.5, 12.5, jeu->map[i][j].x, jeu->map[i][j].y, scale, scale, jeu->map[i][j].rotation*PI/2, 0) ;
            }
            //placement des terrains
            if(verifierPlacementTerrain(jeu, i, j) == true) {
                int type = jeu->map[i][j].type ;
                if(type == TERRAIN) {
                    al_draw_scaled_bitmap(jeu->habitations[TERRAIN].image, 0, 0, jeu->habitations[TERRAIN].width, jeu->habitations[TERRAIN].height, jeu->map[i][j].x - 5*CASEX_X/2, jeu->map[i][j].y - 5*CASEX_X/2, 3*CASEX_X, 3*CASEX_X, 0) ;
                    al_draw_scaled_bitmap(jeu->habitations[CONSTRUCTION].image, 0, 0, jeu->habitations[CONSTRUCTION].width, jeu->habitations[CONSTRUCTION].height, jeu->map[i][j].x - 5*CASEX_X/2, jeu->map[i][j].y - 5*CASEX_X/2, 3*CASEX_X, 3*CASEX_X, 0) ;
                }
                else if(type == IMMEUBLE) {
                    al_draw_scaled_bitmap(jeu->habitations[IMMEUBLE].image, 0, 0, jeu->habitations[IMMEUBLE].width, jeu->habitations[IMMEUBLE].height, jeu->map[i][j].x - 5*CASEX_X/2, jeu->map[i][j].y - 9*CASEX_X/2, CASEX_X*3, CASEX_X*5, 0);
                }
                else if(type == GRATTE_CIEL) {
                    al_draw_scaled_bitmap(jeu->habitations[GRATTE_CIEL].image, 0, 0, jeu->habitations[GRATTE_CIEL].width, jeu->habitations[GRATTE_CIEL].height, jeu->map[i][j].x - 5*CASEX_X/2, jeu->map[i][j].y - 11*CASEX_X/2, CASEX_X*3, CASEX_X*6, 0);
                }
                else al_draw_scaled_bitmap(jeu->habitations[type].image, 0, 0, jeu->habitations[type].width, jeu->habitations[type].height, jeu->map[i][j].x - 5*CASEX_X/2, jeu->map[i][j].y - 7*CASEX_X/2, CASEX_X*3, CASEX_X*4, 0);
            }
            if (jeu->map[i][j].type == CENTRALE) {
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(255, 140, 0));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(200, 200, 140), 1);
            }
            if (jeu->map[i][j].type == CHATEAU) {
                al_draw_filled_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(240, 230, 140));
                al_draw_rectangle(jeu->map[i][j].x - CASEX_X / 2, jeu->map[i][j].y - CASEX_X / 2,jeu->map[i][j].x + CASEX_X / 2, jeu->map[i][j].y + CASEX_X / 2,al_map_rgb(200, 200, 140), 1);
            }
        }
    }


    ///EVOLUTION DES BATIMENTS (Il n'y a que la vérification du temps la)
    for (int i = 0; i < jeu->nbMaisons; i++) {
        if (jeu->time[1].secondes - jeu->tabHabitations[i].tempsEvolution == 5) {
            jeu->tabHabitations[i].tempsEvolution = jeu->time[1].secondes;
            if (jeu->tabHabitations[i].evolution == 0 && jeu->capaciteElec > jeu->nbHabitants) {
                if (jeu->tabHabitations[i].type != GRATTE_CIEL) {
                    jeu->tabHabitations[i].tempsEvolution = jeu->time[1].secondes;
                    jeu->tabHabitations[i].type++;
                    switch(jeu->tabHabitations[i].type){
                        case CABANE :{
                            jeu->nbHabitants +=10;
                            break;
                            }
                            case MAISON : {
                                jeu->nbHabitants += 40;
                                break;
                            }
                            case IMMEUBLE : {
                                jeu->nbHabitants += 50;
                                break;
                            }
                            case GRATTE_CIEL : {
                                jeu->nbHabitants += 900;
                                break;
                            }
                    }
                    jeu->capaciteElec -= jeu->nbHabitants;
                    int caseBatx = jeu->tabHabitations[i].caseX;
                    int caseBaty = jeu->tabHabitations[i].caseY;
                    for (int j = 0; j < 3; j++) {
                        jeu->map[caseBatx - 1][caseBaty - 1 + j].type++;
                        jeu->map[caseBatx][caseBaty - 1 + j].type++;
                        jeu->map[caseBatx + 1][caseBaty - 1 + j].type++;
                    }
                }
                else if (jeu->tabHabitations[i].type == GRATTE_CIEL) {
                    jeu->tabHabitations[i].evolution = 1;
                }
            }
            else{
                jeu->tabHabitations[i].evolution = 0;
            }
        }
    }
}



///ON DETERMINE SUR QUELLE CASE SE SITUE LA SOURIS
int determinerCaseX(int mouse_x) {
    int caseX;
    caseX = mouse_x - MAPX;
    caseX = caseX / CASEX_X;
    if (caseX > 45 || caseX < 0) {
        return 0;
    }
    else return (int) caseX;
}

int determinerCaseY(int mouse_x) {
    int caseY ;
    caseY = mouse_x - MAPY ;
    caseY = caseY/CASEX_X ;
    if(caseY > 35 || caseY < 0) {
        return 0 ;
    }

    else return (int) caseY;

}


bool routeProximiteMaison(Jeu** jeu, int caseSourisX, int caseSourisY){
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

bool routeProximiteCentrale(Jeu** jeu, int caseSourisX, int caseSourisY){
    int routeProxi = 0 ;
    for(int i=0 ; i <6; i++){
        if((*jeu)->map[caseSourisX-3][caseSourisY+2-i].type==ROUTE || (*jeu)->map[caseSourisX+2][caseSourisY+2-i].type==ROUTE){
            routeProxi++;
        }
        if(i < 4) {
            if ((*jeu)->map[caseSourisX + 1 - i][caseSourisY - 4].type == ROUTE || (*jeu)->map[caseSourisX + 1 - i][caseSourisY + 3].type == ROUTE) {
                routeProxi++;
            }
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
    if(caseLibre == 24) {
        return true ;
    }
    else return false ;
}

///POUR L'AFFICHAGE DES ROUTES
void verifierAffichageRoute(Jeu** jeu, int caseSourisX, int caseSourisY) {
    if ((*jeu)->map[caseSourisX + 1][caseSourisY].type == ROUTE) {
        (*jeu)->map[caseSourisX][caseSourisY].route[DROITE] = 1 ;
    }
    if ((*jeu)->map[caseSourisX - 1][caseSourisY].type == ROUTE) {
        (*jeu)->map[caseSourisX][caseSourisY].route[GAUCHE] = 1 ;
    }
    if ((*jeu)->map[caseSourisX][caseSourisY + 1].type == ROUTE) {
        (*jeu)->map[caseSourisX][caseSourisY].route[BAS] = 1 ;

    }
    if ((*jeu)->map[caseSourisX][caseSourisY - 1].type == ROUTE) {
        (*jeu)->map[caseSourisX][caseSourisY].route[HAUT] = 1 ;
    }
}

int combinaison(Jeu jeu, int caseSourisX, int caseSourisY, int* rotation) {
    ///En gros, c'est une combinaison en binaire (ducoup ya 16 possibilités de routes au total)
    int combinaison = jeu.map[caseSourisX][caseSourisY].route[BAS] + jeu.map[caseSourisX][caseSourisY].route[HAUT]*2 + jeu.map[caseSourisX][caseSourisY].route[GAUCHE] * 4 + jeu.map[caseSourisX][caseSourisY].route[DROITE]*8 ;
    if(combinaison == 0) {
        return 0 ;
    }

    ///ROUTE 1 (1 direction seulement)
    else if(combinaison > 0 && combinaison < 4) {
        *rotation = 4 ;
        return 1;
    }
    else if(combinaison == 4 || combinaison == 8 || combinaison == 12) {
        *rotation = 1 ;
        return 1;
    }

    ///ROUTE 2 (2 directions)
    else if(combinaison == 5) {
        *rotation = 2 ;
        return 2;
    }
    else if(combinaison == 6) {
        *rotation = 3 ;
        return 2;
    }
    else if(combinaison == 9) {
        *rotation = 1 ;
        return 2;
    }
    else if(combinaison == 10) {
        *rotation = 0;
        return 2;
    }

    ///ROUTE 3 (3 directions)
    else if(combinaison == 7) {
        *rotation = 3 ;
        return 3;
    }
    else if(combinaison == 11) {
        *rotation = 1 ;
        return 3;
    }
    else if(combinaison == 13) {
        *rotation = 2 ;
        return 3;
    }
    else if(combinaison == 14) {
        *rotation = 0 ;
        return 3;
    }

    ///ROUTE 4 (4 directions)
    else {
        *rotation = 2 ;
        return 4 ;
    }
}

bool verifierPlacementTerrain(Jeu* jeu, int caseX, int caseY) {
    for(int i = 0 ; i < jeu->nbMaisons ; i++) {
        if(jeu->tabHabitations[i].caseX+1 == caseX && jeu->tabHabitations[i].caseY+1 == caseY){
            return true ;
        }
    }
    return false ;
}