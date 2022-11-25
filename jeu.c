#include "jeu.h"


void initImage(Jeu** jeu) {
    for(int i = 0 ; i<4 ;i++) {
        (*jeu)->route[i].width = 25 ;
        (*jeu)->route[i].height = 25 ;
    }

    (*jeu)->habitations[TERRAIN].width = 75 ;
    (*jeu)->habitations[TERRAIN].height = 75 ;

    (*jeu)->habitations[CABANE].width = 112 ;
    (*jeu)->habitations[CABANE].height = 147 ;

    (*jeu)->habitations[MAISON].width = 112 ;
    (*jeu)->habitations[MAISON].height = 160 ;

    (*jeu)->habitations[IMMEUBLE].width = 439 ;
    (*jeu)->habitations[IMMEUBLE].height = 468 ;

    (*jeu)->habitations[GRATTE_CIEL].width = 134 ;
    (*jeu)->habitations[GRATTE_CIEL].height = 342 ;

    (*jeu)->habitations[CONSTRUCTION].width = 129 ;
    (*jeu)->habitations[CONSTRUCTION].height = 112 ;

    (*jeu)->centrale[0].width = 195 ;
    (*jeu)->centrale[0].height = 355 ;

    (*jeu)->centrale[1].width = 399 ;
    (*jeu)->centrale[1].height = 589 ;

    (*jeu)->icone[0].width = 1024 ;
    (*jeu)->icone[0].height = 985 ;

    (*jeu)->icone[1].width = 512 ;
    (*jeu)->icone[1].height = 512 ;

    (*jeu)->icone[2].width = 288 ;
    (*jeu)->icone[2].height = 279 ;

    (*jeu)->icone[3].width = 321 ;
    (*jeu)->icone[3].height = 307 ;

    (*jeu)->icone[4].width = 309 ;
    (*jeu)->icone[4].height = 305 ;

    (*jeu)->icone[5].width = 320 ;
    (*jeu)->icone[5].height = 305 ;

}

void initJeu(Jeu* jeu) {
    initImage(&jeu) ;
    jeu->time[0].secondes =  jeu->time[0].minutes = jeu->nbHabitants = jeu->mouse_x = jeu->mouse_y = jeu->nbCentrale = jeu->nbChateau = 0;
    jeu->argent= ARGENTDEP;
    jeu->niveauAfficher = ROUTIER ;
    jeu->mouseIsPressed = false ;
    jeu->objetSelectionne = RIEN ;
    jeu->toolboxX = 1500 ;
    jeu->zoom.z = 0 ;
    jeu->zoom.CaseX_X = jeu->zoom.oldCaseX_X = CASEX_X ;
    jeu->zoom.mapX = jeu->zoom.oldMapX = MAPX ;
    jeu->zoom.mapY = jeu->zoom.oldMapY = MAPY ;
    jeu->time[0].secondes = 0 ;
    jeu->time[0].minutes = 0 ;
    jeu->time[1].dixieme = 0 ;
    jeu->time[1].secondes = 0 ;
    jeu->modeCapitaliste =0;
    jeu->modeCommuniste = 0;



    for(int i = 0 ; i < COLONNE ; i++) {
        for(int j = 0 ; j < LIGNE ; j++) {
            jeu->map[i][j].type = RIEN ;
            jeu->map[i][j].x = MAPX + CASEX_X * i + CASEX_X / 2  ;
            jeu->map[i][j].y = MAPY + CASEX_X * j + CASEX_X / 2  ;
            jeu->map[i][j].numConstruction = 0  ;
            jeu->map[i][j].electricite = 0  ;
            jeu->map[i][j].eau = 0  ;
            jeu->matriceChateau_Maison[i][j] = 0 ;
            for(int k = 0 ; k < 4 ; k++) {
                jeu->map[i][j].route[k] = 0 ;
            }
            jeu->map[i][j].rotation = 0 ;
        }
    }
    for(int i = 0 ; i < MAX ; i++){
        jeu->tabHabitations[i].evolution = 0 ;
        for(int j = 0 ; j < 10 ; j++) {
            jeu->tabHabitations[i].filePrioriteDistance[j] = -1;
        }
    }
}

void zoom(Jeu* jeu, int caseX, int caseY) {
    if(jeu->zoom.CaseX_X != CASEX_X) {
        jeu->zoom.mapX = jeu->zoom.oldMapX + caseX * jeu->zoom.oldCaseX_X - caseX * jeu->zoom.CaseX_X;
        jeu->zoom.mapY = jeu->zoom.oldMapY + caseY * jeu->zoom.oldCaseX_X - caseY * jeu->zoom.CaseX_X;
    }
    else {
        jeu->zoom.mapX = MAPX ;
        jeu->zoom.mapY = MAPY ;
    }
    jeu->zoom.oldMapX = jeu->zoom.mapX ;
    jeu->zoom.oldMapY = jeu->zoom.mapY ;
    jeu->zoom.oldCaseX_X = jeu->zoom.CaseX_X ;
}

void deplacerMap(Jeu* jeu) {
    jeu->zoom.oldMapX = jeu->zoom.mapX ;
    jeu->zoom.oldMapY = jeu->zoom.mapY ;
    if(jeu->zoom.direction[HAUT] == 1) {
        if(jeu->zoom.mapY + 20 < MAPY) {
            jeu->zoom.mapY += 20 ;
        }
    }
    if(jeu->zoom.direction[BAS] == 1) {
        if(jeu->zoom.mapY + 35 * jeu->zoom.CaseX_X - 20 > MAPY + 35 * CASEX_X ) {
            jeu->zoom.mapY -= 20 ;
        }
    }
    if(jeu->zoom.direction[DROITE] == 1) {
        if(jeu->zoom.mapX + 45 * jeu->zoom.CaseX_X - 20 > MAPX + 45 * CASEX_X ) {
            jeu->zoom.mapX -= 20 ;
        }
    }
    if(jeu->zoom.direction[GAUCHE] == 1) {
        if(jeu->zoom.mapX + 20 < MAPX) {
            jeu->zoom.mapX += 20 ;
        }
    }
}

void dessinerTerrain(Jeu* jeu) {
    al_draw_rectangle(jeu->zoom.mapX, jeu->zoom.mapY, jeu->zoom.mapX + 45 * jeu->zoom.CaseX_X, jeu->zoom.mapY + 35 * jeu->zoom.CaseX_X, al_map_rgb(235, 235, 235), 1) ;
    for (int i = 0; i < 35; i++) {
        al_draw_line(jeu->zoom.mapX, jeu->zoom.mapY + jeu->zoom.CaseX_X * i, jeu->zoom.mapX + 45 * jeu->zoom.CaseX_X, jeu->zoom.mapY + jeu->zoom.CaseX_X * i, al_map_rgb(235, 235, 235), 1);
    }
    for (int i = 0; i < 45; i++) {
        al_draw_line(jeu->zoom.mapX + jeu->zoom.CaseX_X * i, jeu->zoom.mapY, jeu->zoom.mapX + jeu->zoom.CaseX_X * i, jeu->zoom.mapY + 35 * jeu->zoom.CaseX_X, al_map_rgb(235, 235, 235), 1);
    }
}

void temps(Temps* time, int compteur, int numTimer) {
    time->dixieme += 2 ;
    if(compteur%50 == 0){
        time->secondes++ ;
        time->dixieme = 0.00f ;
    }
    if(time->secondes == 60 && numTimer == 0) {
        time->minutes++ ;
        time->secondes = 0 ;
    }
}

void dessinerJeu(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu* jeu) {
    ///CASE SUR LAQUELLE SE TROUVE LA SOURIS
    int caseX = determinerCaseX(jeu->mouse_x, jeu->zoom.mapX, jeu->zoom.CaseX_X);
    int caseY = determinerCaseY(jeu->mouse_y, jeu->zoom.mapY, jeu->zoom.CaseX_X);

    /// CORDONNEES (caseX,caseY) DE LA CASE (X,Y)
    float x_CaseXY = jeu->map[caseX][caseY].x;
    float y_CaseXY = jeu->map[caseX][caseY].y;

    ///RAPPORT TAILLE CASE ACTUELLE ET TAILLE ORIGINAL (pour zoomer
    float scale = jeu->zoom.CaseX_X / 25;
    int mapX = jeu->zoom.mapX;
    int mapY = jeu->zoom.mapY;
    int caseX_X = jeu->zoom.CaseX_X;

    for (int i = 0; i < COLONNE; i++) {
        for (int j = 0; j < LIGNE; j++) {
            jeu->map[i][j].x = mapX + caseX_X * i + caseX_X / 2;
            jeu->map[i][j].y = mapY + caseX_X * j + caseX_X / 2;
        }
    }


    dessinerTerrain(jeu);

   // al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 500, 500, ALLEGRO_ALIGN_CENTER, "%d, %d",jeu->time[0].secondes, (int)jeu->time[0].dixieme);

    ///TIMER
    if (jeu->time[0].secondes < 10) {
        al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : 0%d",
                      jeu->time[0].minutes, jeu->time[0].secondes);
    } else
        al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 990, 7, ALLEGRO_ALIGN_CENTER, "%d : %d",
                      jeu->time[0].minutes, jeu->time[0].secondes);
    ///DESSINER NB HABITANT
    al_draw_scaled_bitmap(jeu->icone[0].image, 0, 0, 1024, 985, 900, 5, 40, 30, 0);


    al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 880, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu->nbHabitants);
    ///DESSINER ARGENT
    al_draw_textf(smallFont, al_map_rgb(47, 58, 124), 700, 7, ALLEGRO_ALIGN_CENTER, "ARGENT : %d", jeu->argent);


    ///////////AFFICHAGE DU NIVEAU O///////////////

    if (jeu->niveauAfficher == ROUTIER) {

        ///ON SELECTIONNE UN OBJET
        switch (jeu->objetSelectionne) {
            case ROUTE : {
                //Si on est dans la grille du jeu, il dessine le carré dans la bonne case
                if (jeu->mouse_x > mapX && jeu->mouse_x < mapX + 45 * caseX_X && jeu->mouse_y > mapY &&
                    jeu->mouse_y < mapY + 35 * caseX_X) {
                    al_draw_filled_rectangle(x_CaseXY - caseX_X / 2, y_CaseXY - caseX_X / 2, x_CaseXY + caseX_X / 2,
                                             y_CaseXY + caseX_X / 2, al_map_rgb(50, 50, 50));
                } else
                    al_draw_filled_rectangle(jeu->mouse_x - caseX_X / 2, jeu->mouse_y - caseX_X / 2,
                                             jeu->mouse_x + caseX_X / 2, jeu->mouse_y + caseX_X / 2,
                                             al_map_rgb(50, 50, 50));
                break;
            }
            case TERRAIN : {
                //Si on est dans la grille du jeu, il dessine le carré dans les bonnes cases
                if (jeu->mouse_x > mapX && jeu->mouse_x < mapX + 45 * caseX_X && jeu->mouse_y > mapY &&
                    jeu->mouse_y < mapY + 35 * caseX_X) {
                    al_draw_scaled_bitmap(jeu->habitations[TERRAIN].image, 0, 0, jeu->habitations[TERRAIN].width,jeu->habitations[TERRAIN].height, x_CaseXY - 3 * caseX_X / 2,y_CaseXY - 3 * caseX_X / 2, 3 * caseX_X, 3 * caseX_X, 0);
                    // Si les conditions ne sont pas vérifiés, on affiche le batiments en rouge
                    if (verifierTerrain3_3v2(&jeu, caseX, caseY) == false ||
                        routeProximiteMaison(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 3 * caseX_X / 2, y_CaseXY - 3 * caseX_X / 2,
                                                 x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 3 * caseX_X / 2,
                                                 al_map_rgba(255, 0, 0, 50));
                    }
                }
                break;
            }
            case CHATEAU : {
                if (jeu->mouse_x > mapX && jeu->mouse_x < mapX + 45 * caseX_X && jeu->mouse_y > mapY &&
                    jeu->mouse_y < mapY + 35 * caseX_X) {
                    al_draw_filled_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,al_map_rgb(240, 230, 140));
                    if (verifierTerrain4_6(&jeu, caseX, caseY) == false ||
                        routeProximiteCentrale(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,al_map_rgba(255, 0, 0, 150));
                    }

                }
                break;

            }
            case CENTRALE : {
                if (jeu->mouse_x > mapX && jeu->mouse_x < mapX + 45 * caseX_X && jeu->mouse_y > mapY &&
                    jeu->mouse_y < mapY + 35 * caseX_X) {
                    al_draw_filled_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,al_map_rgb(255, 140, 0));
                    if (verifierTerrain4_6(&jeu, caseX, caseY) == false ||
                        routeProximiteCentrale(&jeu, caseX, caseY) == false) {
                        al_draw_filled_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,al_map_rgba(255, 0, 0, 150));
                    }

                }
                break;
            }
        }


        ///QUAND ON APPUIE SUR LE BOUTON DE LA SOURIS
        if (jeu->mouseIsPressed)  {
            //Quand on appuie sur les icones des batiments, on selectionne un objet
            if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 285) * (jeu->mouse_y - 285) < 49 * 49) {
                jeu->objetSelectionne = ROUTE;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 395) * (jeu->mouse_y - 395) <49 * 49) {
                jeu->objetSelectionne = TERRAIN;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 505) * (jeu->mouse_y - 505) <49 * 49) {
                jeu->objetSelectionne = CHATEAU;
            } else if ((jeu->mouse_x - 1607) * (jeu->mouse_x - 1607) + (jeu->mouse_y - 615) * (jeu->mouse_y - 615) <49 * 49) {
                jeu->objetSelectionne = CENTRALE;
            }
                //Si on n'appuie ni sur les icones, ni sur la grille, on enleve la sélection
            else if ((jeu->mouse_x > 1500 && jeu->mouse_x < 1720 && jeu->mouse_y > 100 && jeu->mouse_y < 815) || !(jeu->mouse_x > mapX && jeu->mouse_x < mapX + 45 * caseX_X && jeu->mouse_y > mapY &&jeu->mouse_y < mapY + 35 * caseX_X)) {
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
                            al_draw_rectangle(x_CaseXY - 3 * caseX_X / 2, y_CaseXY - 3 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 3 * caseX_X / 2,al_map_rgb(255, 0, 0), 4);

                        }
                            //On peut poser le terrain (pas de batiments déjà posé ici), on vérifie maintenant la proximité à une route
                        else if (routeProximiteMaison(&jeu, caseX, caseY) == true && jeu->argent >= 1000) {
                            jeu->argent -= 1000;
                            //On change les données de notre tab 2D
                            for (int i = 0; i < 3; i++) {
                                jeu->map[caseX - 1][caseY + 1 - i].type = TERRAIN;
                                jeu->map[caseX - 1][caseY + 1 - i].numConstruction = jeu->nbMaisons;

                                jeu->map[caseX][caseY + 1 - i].type = TERRAIN;
                                jeu->map[caseX][caseY + 1 - i].numConstruction = jeu->nbMaisons;

                                jeu->map[caseX + 1][caseY + 1 - i].type = TERRAIN;
                                jeu->map[caseX + 1][caseY + 1 - i].numConstruction = jeu->nbMaisons;

                            }
                            //On note la Case dans le tab des Habitations
                            jeu->tabHabitations[jeu->nbMaisons].caseX = caseX;
                            jeu->tabHabitations[jeu->nbMaisons].caseY = caseY;
                            jeu->tabHabitations[jeu->nbMaisons].tempsEvolution = jeu->time[1].secondes;
                            ///POSE DU TERRAIN + CREATION DANS LE TAB
                            if (jeu->nbChateau == 0) {
                                if(jeu->nbMaisons == 0) {
                                    jeu->matrice = calloc(1, sizeof(Matricechat *));
                                    jeu->matrice[0] = calloc(1, sizeof(Matricechat));
                                    jeu->matrice[0][0].distance = 0;
                                    jeu->matrice[0][0].capacite = 1;
                                    jeu->matrice[0][0].quatntitedistribue = 2;
                                    jeu->nbMaisons++;
                                }
                                else {
                                    jeu->nbMaisons++;
                                    jeu->matrice = realloc(jeu->matrice, jeu->nbMaisons*sizeof (Matricechat*)) ;
                                    for(int i = 0; i < jeu->nbMaisons; i++){
                                        jeu->matrice[i] = calloc(1, sizeof (Matricechat)) ;
                                        jeu->matrice[i][0].distance = 0 ;
                                        jeu->matrice[i][0].capacite = 0 ;
                                        jeu->matrice[i][0].quatntitedistribue = 0 ;
                                    }
                                }

                            }
                            else{
                                jeu->nbMaisons++;
                                if(jeu->nbMaisons > 0) {
                                    jeu->matrice = realloc(jeu->matrice , jeu->nbMaisons * sizeof (Matricechat*)) ;
                                    for (int j = 0; j < jeu->nbChateau; j++) {
                                        jeu->matrice[jeu->nbMaisons-1] = calloc(1, sizeof (Matricechat)) ;
                                        jeu->matrice[jeu->nbMaisons-1][j].distance = 0;
                                        jeu->matrice[jeu->nbMaisons-1][j].capacite = 0;
                                        jeu->matrice[jeu->nbMaisons-1][j].quatntitedistribue = 0;
                                    }
                                }
                            }

                        }
                        break;
                    }
                    case CHATEAU : {
                        //Si on peut pas poser le terrain, on le surbrille en rouge
                        if (verifierTerrain4_6(&jeu, caseX, caseY) == false) {
                            al_draw_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,
                                              x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,
                                              al_map_rgb(255, 0, 0), 4);
                        }
                            //Sinon on peut le poser, on verifie donc les routes à cotés
                        else if (routeProximiteCentrale(&jeu, caseX, caseY) == true && jeu->argent >= 100000) {
                            jeu->argent -= 100000;
                            for (int i = 0; i < 6; i++) {
                                jeu->map[caseX - 2][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX - 2][caseY + 2 - i].numConstruction = jeu->nbChateau;

                                jeu->map[caseX - 1][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX - 1][caseY + 2 - i].numConstruction = jeu->nbChateau;

                                jeu->map[caseX][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX][caseY + 2 - i].numConstruction = jeu->nbChateau;

                                jeu->map[caseX + 1][caseY + 2 - i].type = CHATEAU;
                                jeu->map[caseX + 1][caseY + 2 - i].numConstruction = jeu->nbChateau;
                            }
                            jeu->tabChateau[jeu->nbChateau].caseX = caseX;
                            jeu->tabChateau[jeu->nbChateau].caseY = caseY;
                            if (jeu->nbMaisons == 0) {
                                if(jeu->nbChateau == 0) {
                                    jeu->matrice = calloc(1, sizeof(Matricechat *));
                                    jeu->matrice[0] = calloc(1, sizeof(Matricechat));
                                    jeu->matrice[0][0].distance = 0;
                                    jeu->matrice[0][0].capacite = 0;
                                    jeu->matrice[0][0].quatntitedistribue = 0;
                                    jeu->nbChateau++;
                                    jeu->capaciteEau += CAPACITE;
                                }
                                else {
                                    jeu->nbChateau++;
                                    jeu->capaciteEau += CAPACITE;
                                    jeu->matrice[0] = realloc(jeu->matrice[0], jeu->nbChateau*sizeof (Matricechat)) ;
                                    for(int i = 0; i < jeu->nbChateau; i++) {
                                        jeu->matrice[0][i].distance = 0;
                                        jeu->matrice[0][i].capacite = 0;
                                        jeu->matrice[0][i].quatntitedistribue = 0;
                                    }
                                }
                            }
                            else{
                                jeu->nbChateau++;
                                jeu->capaciteEau += CAPACITE;
                                if(jeu->nbChateau > 0) {
                                    for(int i = 0; i < jeu->nbMaisons; i++){
                                        jeu->matrice[i] = realloc(jeu->matrice[i], jeu->nbChateau * sizeof (Matricechat)) ;
                                    }
                                    for(int i = 0; i < jeu->nbMaisons; i++) {
                                        for (int j = 0; j < jeu->nbChateau; j++) {
                                            jeu->matrice[i][jeu->nbChateau-1].distance = 0;
                                            jeu->matrice[i][jeu->nbChateau-1].capacite = 0;
                                            jeu->matrice[i][jeu->nbChateau-1].quatntitedistribue = 0;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case CENTRALE : {
                        //PAREIL QUE LE CHATEAU D'EAU
                        if (verifierTerrain4_6(&jeu, caseX, caseY) == false) {
                            al_draw_rectangle(x_CaseXY - 5 * caseX_X / 2, y_CaseXY - 7 * caseX_X / 2,x_CaseXY + 3 * caseX_X / 2, y_CaseXY + 5 * caseX_X / 2,al_map_rgb(255, 0, 0), 4);
                        } else if (routeProximiteCentrale(&jeu, caseX, caseY) == true && jeu->argent >= 100000) {
                            jeu->argent -= 100000;
                            for (int i = 0; i < 6; i++) {
                                jeu->map[caseX - 2][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX - 2][caseY + 2 - i].numConstruction = jeu->nbCentrale;

                                jeu->map[caseX - 1][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX - 1][caseY + 2 - i].numConstruction = jeu->nbCentrale;

                                jeu->map[caseX][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX][caseY + 2 - i].numConstruction = jeu->nbCentrale;

                                jeu->map[caseX + 1][caseY + 2 - i].type = CENTRALE;
                                jeu->map[caseX + 1][caseY + 2 - i].numConstruction = jeu->nbCentrale;
                            }
                            jeu->tabCentrale[jeu->nbCentrale].caseX = caseX;
                            jeu->tabCentrale[jeu->nbCentrale].caseY = caseY;
                            jeu->tabCentrale[jeu->nbCentrale].electricite += CAPACITE;
                            jeu->tabCentrale[jeu->nbCentrale].capaciteElec += CAPACITE;
                            jeu->tabCentrale[jeu->nbCentrale].quantitedistri = 0;
                            jeu->capacitElec += CAPACITE ;
                            jeu->nbCentrale++;

                        }
                        break;
                    }
                }
            }
        }
        ///DESSIN DES ELEMENTS DE LA MAP
        for (int j = 0; j < LIGNE; j++) {
            for (int i = 0; i < COLONNE; i++) {
                //placement des routes
                if (jeu->map[i][j].type == ROUTE) {
                    verifierAffichageRoute(&jeu, i, j);
                    int quelRoute = combinaison(*jeu, i, j, &jeu->map[i][j].rotation);
                    al_draw_scaled_rotated_bitmap(jeu->route[quelRoute].image, 12.5, 12.5, jeu->map[i][j].x,jeu->map[i][j].y, scale, scale, jeu->map[i][j].rotation * PI / 2, 0);
                }
                //placement des terrains
                else if (verifierPlacementTerrain(jeu, i, j) == true) {
                    int type = jeu->map[i][j].type;
                    if (type == TERRAIN) {
                        al_draw_scaled_bitmap(jeu->habitations[TERRAIN].image, 0, 0, jeu->habitations[TERRAIN].width,jeu->habitations[TERRAIN].height, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 5 * caseX_X / 2, 3 * caseX_X, 3 * caseX_X, 0);
                        al_draw_scaled_bitmap(jeu->habitations[CONSTRUCTION].image, 0, 0,jeu->habitations[CONSTRUCTION].width,jeu->habitations[CONSTRUCTION].height, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 5 * caseX_X / 2, 3 * caseX_X, 3 * caseX_X, 0);
                    } else if (type == IMMEUBLE) {
                        al_draw_scaled_bitmap(jeu->habitations[IMMEUBLE].image, 0, 0, jeu->habitations[IMMEUBLE].width,jeu->habitations[IMMEUBLE].height, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 9 * caseX_X / 2, caseX_X * 3, caseX_X * 5, 0);
                    } else if (type == GRATTE_CIEL) {
                        al_draw_scaled_bitmap(jeu->habitations[GRATTE_CIEL].image, 0, 0,jeu->habitations[GRATTE_CIEL].width, jeu->habitations[GRATTE_CIEL].height,jeu->map[i][j].x - 5 * caseX_X / 2, jeu->map[i][j].y - 11 * caseX_X / 2,caseX_X * 3, caseX_X * 6, 0);
                    } else
                        al_draw_scaled_bitmap(jeu->habitations[type].image, 0, 0, jeu->habitations[type].width,jeu->habitations[type].height, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 7 * caseX_X / 2, caseX_X * 3, caseX_X * 4, 0);
                } else if (verifierPlacementCentrale(jeu, i, j, 1) == true && jeu->map[i][j].type == CHATEAU) {
                    al_draw_scaled_bitmap(jeu->centrale[2].image, 0, 0, 64, 96, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 7 * caseX_X / 2, caseX_X * 4, caseX_X * 6, 0);
                    al_draw_scaled_bitmap(jeu->centrale[0].image, 0, 0, jeu->centrale[0].width, jeu->centrale[0].height,jeu->map[i][j].x - 2*  caseX_X, jeu->map[i][j].y - 5 * caseX_X,caseX_X * 3, caseX_X * 6, 0);

                } else if (verifierPlacementCentrale(jeu, i, j, 0) == true) {
                    al_draw_scaled_bitmap(jeu->centrale[2].image, 0, 0, 64, 96, jeu->map[i][j].x - 5 * caseX_X / 2,jeu->map[i][j].y - 7 * caseX_X / 2, caseX_X * 4, caseX_X * 6, 0);
                    al_draw_scaled_bitmap(jeu->centrale[1].image, 0, 0, jeu->centrale[1].width, jeu->centrale[1].height,jeu->map[i][j].x - 5 * caseX_X / 2 + caseX_X/8,jeu->map[i][j].y - 9 * caseX_X / 2, caseX_X * 4, caseX_X * 6, 0);
                    for(int c = 0; c< jeu->nbCentrale; c++){
                        al_draw_textf(smallFont, al_map_rgb(255, 255, 255),jeu->map[jeu->tabCentrale[c].caseX][jeu->tabCentrale[c].caseY].x,jeu->map[jeu->tabCentrale[c].caseX][jeu->tabCentrale[c].caseY].y, ALLEGRO_ALIGN_CENTER, "%d/%d", jeu->tabCentrale[c].quantitedistri,jeu->tabCentrale[c].electricite);
                    }
                }
            }
        }
    }
    ///EVOLUTION DES BATIMENTS (Il n'caseY a que la vérification du temps la)
    for (int i = 0; i < jeu->nbMaisons; i++) {
        int evolution = determinerDistanceMaison(&jeu, i);
        if (jeu->time[1].secondes - jeu->tabHabitations[i].tempsEvolution == 10 && evolution != 0) {
            jeu->tabHabitations[i].tempsEvolution = jeu->time[1].secondes;
            int numCentrale = prioDistance(jeu, i) ;
            if (jeu->tabHabitations[i].evolution == 0  && numCentrale != -1) {
                if (jeu->tabHabitations[i].type != GRATTE_CIEL) {
                    jeu->tabHabitations[i].tempsEvolution = jeu->time[1].secondes;
                    jeu->tabHabitations[i].type++;
                    jeu->argent += 10 * jeu->nbHabitants;

                    switch (jeu->tabHabitations[i].type) {
                        case CABANE : {
                            jeu->nbHabitants += 10;
                            jeu->tabHabitations[i].nbHabitant = 10;
                            jeu->tabCentrale[numCentrale].quantitedistri += 10;
                            break;
                        }
                        case MAISON : {
                            jeu->tabHabitations[i].nbHabitant = 50;
                            jeu->nbHabitants += 40;
                            jeu->tabCentrale[numCentrale].quantitedistri += 40;
                            break;
                        }
                        case IMMEUBLE : {
                            jeu->nbHabitants += 50;
                            jeu->tabHabitations[i].nbHabitant = 100;
                            jeu->tabCentrale[numCentrale].quantitedistri+=50;
                            break;
                        }
                        case GRATTE_CIEL : {
                            jeu->nbHabitants += 900;
                            jeu->tabHabitations[i].nbHabitant = 1000;
                            jeu->tabCentrale[numCentrale].quantitedistri += 900;
                            break;
                        }
                    }
                    int caseBatx = jeu->tabHabitations[i].caseX;
                    int caseBaty = jeu->tabHabitations[i].caseY;
                    for (int j = 0; j < 3; j++) {
                        jeu->map[caseBatx - 1][caseBaty - 1 + j].type++;
                        jeu->map[caseBatx][caseBaty - 1 + j].type++;
                        jeu->map[caseBatx + 1][caseBaty - 1 + j].type++;
                    }
                } else if (jeu->tabHabitations[i].type == GRATTE_CIEL) {
                    jeu->tabHabitations[i].evolution = 1;
                }
            } else {
                jeu->tabHabitations[i].evolution = 0;
            }
        }
    }


    for(int i = 0 ; i < jeu->nbMaisons ; i++) {
        determinerDistanceMaison(&jeu, i) ;
    }
    dessinerToolbox(jeu);
    dessinerNiveau(smallFont, font, &jeu) ;

    for(int i = 0 ; i < jeu->nbMaisons ; i++) {
        al_draw_textf(smallFont, al_map_rgb(0, 255, 0), jeu->map[jeu->tabHabitations[i].caseX][jeu->tabHabitations[i].caseY].x - 50, jeu->map[jeu->tabHabitations[i].caseX][jeu->tabHabitations[i].caseY].y - 50, 0, "%d", jeu->tabHabitations[i].distance) ;
    }
}

void dessinerNiveau(ALLEGRO_FONT* smallFont, ALLEGRO_FONT* font, Jeu** jeu) {
    ///TOOLBOX
    al_draw_filled_rounded_rectangle(-10, 100, 205, 815, 10, 10, al_map_rgb(150, 150, 150));
    al_draw_rounded_rectangle(-10, 100, 205, 815, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(-10, 99, 206, 816, 10, 10, al_map_rgb(255, 255, 255), 1);

    ///NIVEAU 0 SI PRESSEe
    if ((*jeu)->mouse_x > 40 && (*jeu)->mouse_x < 165 && (*jeu)->mouse_y > 140 && (*jeu)->mouse_y < 265) {
        if ((*jeu)->mouseIsPressed == true) {
            (*jeu)->niveauAfficher = ROUTIER;
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
    if ((*jeu)->mouse_x > 40 && (*jeu)->mouse_x < 165 && (*jeu)->mouse_y > 290 && (*jeu)->mouse_y < 415) {
        if ((*jeu)->mouseIsPressed == true) {
            (*jeu)->niveauAfficher = EAU;
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
    if ((*jeu)->mouse_x > 40 && (*jeu)->mouse_x < 165 && (*jeu)->mouse_y > 440 && (*jeu)->mouse_y < 565) {
        if ((*jeu)->mouseIsPressed == true) {
            (*jeu)->niveauAfficher = ELECTRICITE;
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
    al_draw_textf(smallFont, al_map_rgb(0, 0, 0), 100, 700, ALLEGRO_ALIGN_CENTER, "Niveau %d", (*jeu)->niveauAfficher);
    barreicone(smallFont, *jeu);

    if((*jeu)->niveauAfficher == ROUTIER) {
        if((*jeu)->toolboxX >= 1500) {
            (*jeu)->toolboxX -= 10 ;
        }
    }
    else if((*jeu)->toolboxX <= 1720) {
        (*jeu)->toolboxX += 10 ;
    }

}
void dessinerToolbox(Jeu* jeu) {
///DESSINER PARTIE CONSTRUCTION
    al_draw_filled_rounded_rectangle(jeu->toolboxX, 100, jeu->toolboxX + 220, 815, 10, 10, al_map_rgb(150, 150, 150));
    al_draw_rounded_rectangle(jeu->toolboxX, 100, jeu->toolboxX + 220, 815, 10, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_rounded_rectangle(jeu->toolboxX, 99, jeu->toolboxX + 220, 816, 10, 10, al_map_rgb(255, 255, 255), 1);

    //Dessiner les icones des batiments
    al_draw_scaled_bitmap(jeu->icone[1].image, 0, 0, jeu->icone[1].width, jeu->icone[1].height, jeu->toolboxX + 65, 125, 85, 85, 0);

    al_draw_scaled_bitmap(jeu->icone[2].image, 0, 0, jeu->icone[2].width, jeu->icone[2].height, jeu->toolboxX + 58, 235, 100, 100, 0);
    al_draw_circle(jeu->toolboxX + 107, 285, 49, al_map_rgb(0, 0, 0), 4);

    al_draw_scaled_bitmap(jeu->icone[3].image, 0, 0, jeu->icone[3].width, jeu->icone[3].height, jeu->toolboxX + 58, 345, 100, 100, 0);
    al_draw_circle(jeu->toolboxX + 107, 395, 49, al_map_rgb(0, 0, 0), 4);

    al_draw_scaled_bitmap(jeu->icone[4].image, 0, 0, jeu->icone[4].width, jeu->icone[4].height, jeu->toolboxX + 58, 455, 100, 100, 0);
    al_draw_circle(jeu->toolboxX + 107, 505, 49, al_map_rgb(0, 0, 0), 4);

    al_draw_scaled_bitmap(jeu->icone[5].image, 0, 0, jeu->icone[5].width, jeu->icone[5].height, jeu->toolboxX + 58, 565, 100, 100, 0);
    al_draw_circle(jeu->toolboxX + 107, 615, 49, al_map_rgb(0, 0, 0), 4);

    switch (jeu->objetSelectionne) {
        case ROUTE : {
            al_draw_circle(jeu->toolboxX + 107, 285, 49, al_map_rgb(233, 30, 23), 4);
            break ;
        }
        case TERRAIN : {
            al_draw_circle(jeu->toolboxX + 107, 395, 49, al_map_rgb(233, 30, 23), 4);
            break ;
        }
        case CENTRALE : {
            al_draw_circle(jeu->toolboxX + 107, 615, 49, al_map_rgb(233, 30, 23), 4);
            break ;
        }
        case CHATEAU : {
            al_draw_circle(jeu->toolboxX + 107, 505, 49, al_map_rgb(233, 30, 23), 4);
            break ;
        }
    }
}
void barreicone(ALLEGRO_FONT*smallFont ,Jeu*jeu){
    // al_draw_filled_rounded_rectangle(3, 10, 400, 80, 5, 5, al_map_rgb(73, 132, 171));
    // al_draw_rounded_rectangle( 3, 10, 400, 80, 5, 5, al_map_rgb(73, 132, 171), 4);
    al_draw_scaled_bitmap(jeu->icone[6].image, 0,0, 475,336, 10, 3, 75, 42, 0);
    al_draw_scaled_bitmap(jeu->icone[7].image, 0, 0, 559, 447, 10, 20, 110, 80, 0 );
    al_draw_scaled_bitmap(jeu->icone[8].image, 0, 0, 512, 512, 1430, 22, 75, 45, 0);
    //al_draw_scaled_bitmap(jeu->icone[0].image, 0, 0, 1024, 985, 300, 31, 75, 45, 0);
    al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 1575, 25, ALLEGRO_ALIGN_CENTER, "%d", jeu->argent);
    al_draw_textf(smallFont, al_map_rgb(235, 235, 235), 180, 50, ALLEGRO_ALIGN_CENTER, ": %d", jeu->capaciteEau);
    al_draw_scaled_bitmap(jeu->icone[9].image, 0, 0, 978, 371, 1533, 710, 130, 80, 0 );
    al_draw_scaled_bitmap(jeu->icone[10].image, 0, 0, 273, 204, 1470, 820, 150, 110, 0);
    al_draw_scaled_bitmap(jeu->icone[11].image, 0, 0, 360, 362, 1575, 870, 90, 60, 0);

}

///ON DETERMINE SUR QUELLE CASE SE SITUE LA SOURIS
int determinerCaseX(int mouse_x, int mapX, int caseX_X) {
    int caseX;
    caseX = mouse_x - mapX;
    caseX = caseX / caseX_X;
    if (caseX > 45 || caseX < 0) {
        return 0;
    }
    else return (int) caseX;
}
int determinerCaseY(int mouse_x, int mapY, int caseX_X) {
    int caseY ;
    caseY = mouse_x - mapY ;
    caseY = caseY/caseX_X ;
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
// On verifie s'il caseY a une route dans chaque direction, si oui, alors on écrit 1 dans la case associée
// Ces 4 numéros vont former une combinaison en binaire.
// Par exemple, 0000 veut dire que c'est une route toute seule (route0.png)
// 0001 veut dire qu'il caseY a une route en bas, donc c'est route1.png, on fait ça fait pour toutes les 16 possibilites
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
bool verifierPlacementCentrale(Jeu* jeu, int caseX, int caseY, int type) {
    if (type) {
        for (int i = 0; i < jeu->nbChateau; i++) {
            if (jeu->tabChateau[i].caseX == caseX && jeu->tabChateau[i].caseY == caseY) {
                return true;
            }
        }
        return false;
    } else {
        for (int i = 0; i < jeu->nbCentrale; i++) {
            if (jeu->tabCentrale[i].caseX == caseX && jeu->tabCentrale[i].caseY == caseY) {
                return true;
            }
        }
        return false;
    }
}



int verifCentrale(Jeu* jeu, Habitation tabHabitations[jeu->nbHabitants],int i){
    int p=0;
    switch(tabHabitations[i].type){
        case TERRAIN: {
            p= 10;
        }
        case CABANE: {
            p= 40;
        }
        case MAISON: {
            p= 50;
        }
        case IMMEUBLE: {
            p= 900;
        }
    }
    return p;

}

int determinerDistanceMaison(Jeu** jeu,int quelleMaison) {
    int caseX = (*jeu)->tabHabitations[quelleMaison].caseX;
    int caseY = (*jeu)->tabHabitations[quelleMaison].caseY;
    int bfsFini = 0;
    int relie = 0 ;
    int distance = 0;
    int numHab = 0 ;
    int nbFile = 0 ;
    int pd ;


    for (int i = 0; i < 3; i++) {
        if ((*jeu)->map[caseX - 2][caseY + 1 - i].type == ROUTE) {
            caseX = caseX - 2;
            caseY = caseY + 1 - i;
            break;
        } else if ((*jeu)->map[caseX + 2][caseY + 1 - i].type == ROUTE) {
            caseX = caseX + 2;
            caseY = caseY + 1 - i;
            break;
        } else if ((*jeu)->map[caseX + 1 - i][caseY - 2].type == ROUTE) {
            caseX = caseX + 1 - i;
            caseY = caseY - 2;
            break;
        } else if ((*jeu)->map[caseX + 1 - i][caseY + 2].type == ROUTE) {
            caseX = caseX + 1 - i;
            caseY = caseY + 2;
            break;
        }
    }
    typedef struct {
        int caseX, caseY, distance;
    } File;


    File file[10] = {0};
    int bfsMarque[COLONNE][LIGNE] = {0}, longueurFile = 1 ;
    file[0].caseX = caseX ;
    file[0].caseY = caseY ;


    bfsMarque[caseX][caseY] = 1;
    while (!bfsFini) {
        caseX = file->caseX;
        caseY = file->caseY;
        distance = file->distance;
        longueurFile--;
        for (int i = 0; i < longueurFile; i++) {
            file[i].caseX = file[i + 1].caseX;
            file[i].caseY = file[i + 1].caseY;
            file[i].distance = file[i + 1].distance;
        }
        if ((*jeu)->map[caseX][caseY + 1].type == ROUTE && bfsMarque[caseX][caseY + 1] == 0) {
            file[longueurFile].caseX = caseX;
            file[longueurFile].caseY = caseY + 1;
            file[longueurFile].distance = distance + 1 ;
            longueurFile++ ;
            bfsMarque[caseX][caseY+1] = 1 ;

        }
        if((*jeu)->map[caseX - 1][caseY].type == ROUTE && bfsMarque[caseX - 1][caseY]==0) {
            file[longueurFile].caseX = caseX - 1 ;
            file[longueurFile].caseY = caseY ;
            file[longueurFile].distance = distance + 1 ;
            longueurFile++ ;
            bfsMarque[caseX - 1][caseY] = 1 ;

        }
        if((*jeu)->map[caseX][caseY - 1].type == ROUTE && bfsMarque[caseX][caseY - 1] == 0) {
            file[longueurFile].caseX = caseX ;
            file[longueurFile].caseY = caseY - 1;
            file[longueurFile].distance = distance + 1 ;
            longueurFile++ ;
            bfsMarque[caseX][caseY - 1] = 1 ;

        }
        if((*jeu)->map[caseX + 1][caseY].type == ROUTE && bfsMarque[caseX + 1][caseY]==0) {
            file[longueurFile].caseX = caseX + 1 ;
            file[longueurFile].caseY = caseY ;
            file[longueurFile].distance = distance + 1 ;
            longueurFile++ ;
            bfsMarque[caseX + 1][caseY] = 1 ;
        }
        if ((*jeu)->map[caseX][caseY + 1].type == CHATEAU) {
            numHab = (*jeu)->map[caseX][caseY + 1].numConstruction;
            if ((*jeu)->tabHabitations[quelleMaison].distance > distance) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            } else if ((*jeu)->tabHabitations[quelleMaison].distance == 0) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            }

        }
        if ((*jeu)->map[caseX + 1][caseY].type == CHATEAU) {
            numHab = (*jeu)->map[caseX + 1][caseY].numConstruction;
            if ((*jeu)->tabHabitations[quelleMaison].distance > distance) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            } else if ((*jeu)->tabHabitations[quelleMaison].distance == 0) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            }
        }
        if ((*jeu)->map[caseX - 1][caseY].type == CHATEAU) {
            numHab = (*jeu)->map[caseX - 1][caseY].numConstruction;
            if ((*jeu)->tabHabitations[quelleMaison].distance > distance) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            } else if ((*jeu)->tabHabitations[quelleMaison].distance == 0) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            }
        }
        if ((*jeu)->map[caseX][caseY - 1].type == CHATEAU) {
            numHab = (*jeu)->map[caseX][caseY - 1].numConstruction;
            if ((*jeu)->tabHabitations[quelleMaison].distance > distance) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            } else if ((*jeu)->tabHabitations[quelleMaison].distance == 0) {
                (*jeu)->tabHabitations[quelleMaison].distance = distance + 1;
                (*jeu)->matrice[quelleMaison][numHab].distance = distance + 1 ;
            }
        }
        if ((*jeu)->map[caseX][caseY + 1].type == CENTRALE) {
            numHab = (*jeu)->map[caseX][caseY + 1].numConstruction;
            (*jeu)->tabHabitations[quelleMaison].provenanceElec = numHab;
            (*jeu)->tabHabitations[quelleMaison].filePrioriteDistance[nbFile] = numHab ;
            nbFile++ ;
            relie++;
        }
        if ((*jeu)->map[caseX + 1][caseY].type == CENTRALE) {
            numHab = (*jeu)->map[caseX + 1][caseY].numConstruction;
            (*jeu)->tabHabitations[quelleMaison].provenanceElec = numHab;
            (*jeu)->tabHabitations[quelleMaison].filePrioriteDistance[nbFile] = numHab ;
            nbFile++ ;
            relie++;
        }
        if ((*jeu)->map[caseX][caseY - 1].type == CENTRALE) {
            numHab = (*jeu)->map[caseX][caseY - 1].numConstruction;
            (*jeu)->tabHabitations[quelleMaison].provenanceElec = numHab;
            (*jeu)->tabHabitations[quelleMaison].filePrioriteDistance[nbFile] = numHab ;
            nbFile++ ;
            relie++ ;
        }
        if ((*jeu)->map[caseX - 1][caseY].type == CENTRALE) {
            numHab = (*jeu)->map[caseX - 1][caseY].numConstruction;
            (*jeu)->tabHabitations[quelleMaison].provenanceElec = numHab;
            (*jeu)->tabHabitations[quelleMaison].filePrioriteDistance[nbFile] = numHab ;
            nbFile++ ;
            relie++;
        }
        if (longueurFile == 0) {
            bfsFini = 1;
        }
        if((*jeu)->nbMaisons == 9){
            int stopit ;
            pd = 4 ;
        }
    }
    if(relie == 0) {
        return 0;
    }
    else {
        return distance ;
    }
}
void capaciteEau(Jeu** jeu){
   for(int i = 0 ; i < (*jeu)->nbMaisons ; i++) {

   }
}
int prioDistance (Jeu *jeu, int quelleMaison){
    int i = 0 ;
    int suivant =  verifCentrale(jeu, jeu->tabHabitations, i);
    while(jeu->tabHabitations[quelleMaison].filePrioriteDistance[i] != -1){
        if(jeu->tabCentrale[jeu->tabHabitations[quelleMaison].filePrioriteDistance[i]].electricite  - jeu->tabCentrale[jeu->tabHabitations[quelleMaison].filePrioriteDistance[i]].quantitedistri - suivant >= 0){
            return jeu->tabHabitations[quelleMaison].filePrioriteDistance[i] ;
        }
        else{
            i++ ;
        }
    }
    return -1;
}
