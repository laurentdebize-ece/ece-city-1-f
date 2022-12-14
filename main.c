#include "menu.h"
#include "jeu.h"


int main() {
    ///INITIALISATION DU DISPLAY ET DU TIMER
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *times;
    ALLEGRO_EVENT event = {0};

    srand(time(NULL));

    ///INITIALISATION D'ALLEGRO
    assert(al_init());
    al_install_keyboard() ;
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ///CREATION DU DISPLAY
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(1700, 956);
    double height = al_get_display_height(display);
    double width = al_get_display_width(display);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "ECE SimCity");

    ///COULEUR
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);


    ///CREATION DES DONNEES DU JEU
    int isFin = 0, draw = 0, compteur = 0;
    bool mouseIsPressed = false ;
    times = al_create_timer(0.02);
    Menu menu;
    Jeu jeu;
    jeu.width = width ;
    jeu.height = height ;


    ///CHARGEMENT DES IMAGES

    ALLEGRO_BITMAP *background = al_load_bitmap("../Bitmap/Menu/backgroundMenu.jpg");
    menu.deco[0].image = al_load_bitmap("../Bitmap/Menu/bat3.png");
    menu.deco[1].image = al_load_bitmap("../Bitmap/Menu/bat4.png")  ;
    menu.deco[2].image = al_load_bitmap("../Bitmap/Photo/fares.png");
    menu.deco[3].image = al_load_bitmap("../Bitmap/Photo/valentin.png");
    menu.deco[4].image = al_load_bitmap("../Bitmap/Photo/lisa.png");
    menu.deco[5].image = al_load_bitmap("../Bitmap/Photo/eva.png");

    menu.deco[6].image = al_load_bitmap("../Bitmap/map.png");


    jeu.icone[0].image = al_load_bitmap("../Bitmap/Icone/habitant.png");
    jeu.icone[1].image = al_load_bitmap("../Bitmap/Icone/outil.png");
    jeu.icone[2].image = al_load_bitmap("../Bitmap/Icone/route.png");
    jeu.icone[3].image = al_load_bitmap("../Bitmap/Icone/maison.png");
    jeu.icone[4].image = al_load_bitmap("../Bitmap/Icone/chateau_eau.png");
    jeu.icone[5].image = al_load_bitmap("../Bitmap/Icone/centrale.png");
    jeu.icone[12].image = al_load_bitmap("../Bitmap/Icone/demolition.png");

    jeu.icone[6].image = al_load_bitmap("../Bitmap/Icone/EclairOk-removebg-preview.png");
    jeu.icone[7].image = al_load_bitmap("../Bitmap/Icone/IconeEau-removebg-preview.png");
    jeu.icone[8].image = al_load_bitmap("../Bitmap/Icone/coins.png");
    jeu.icone[9].image = al_load_bitmap("../Bitmap/Icone/ece.png");
    jeu.icone[10].image = al_load_bitmap("../Bitmap/Icone/CaptureIconeEcole-removebg-preview.png");
    jeu.icone[11].image = al_load_bitmap("../Bitmap/Icone/PetitEcolier3-removebg-preview.png");
    jeu.icone[13].image = al_load_bitmap("../Bitmap/Menu/chrono.png");


    jeu.route[0].image =  al_load_bitmap("../Bitmap/Batiments/Route0.png");
    jeu.route[1].image =  al_load_bitmap("../Bitmap/Batiments/Route1.png");
    jeu.route[2].image =  al_load_bitmap("../Bitmap/Batiments/Route2.png");
    jeu.route[3].image =  al_load_bitmap("../Bitmap/Batiments/Route3.png");
    jeu.route[4].image =  al_load_bitmap("../Bitmap/Batiments/Route4.png");

    jeu.habitations[TERRAIN].image = al_load_bitmap("../Bitmap/Batiments/terrain.png") ;
    jeu.habitations[CABANE].image = al_load_bitmap("../Bitmap/Batiments/cabane.png") ;
    jeu.habitations[MAISON].image = al_load_bitmap("../Bitmap/Batiments/maison.png") ;
    jeu.habitations[IMMEUBLE].image = al_load_bitmap("../Bitmap/Batiments/immeuble.png") ;
    jeu.habitations[GRATTE_CIEL].image = al_load_bitmap("../Bitmap/Batiments/gratte_ciel.png") ;
    jeu.habitations[CONSTRUCTION].image = al_load_bitmap("../Bitmap/Batiments/construction.png") ;
    jeu.centrale[0].image = al_load_bitmap("../Bitmap/Batiments/chateau_eau.png") ;
    jeu.centrale[1].image = al_load_bitmap("../Bitmap/Batiments/centrale.png") ;
    jeu.centrale[2].image = al_load_bitmap("../Bitmap/Batiments/terrainRoute.png") ;

    ALLEGRO_BITMAP* staline = al_load_bitmap("../Bitmap/Menu/stalion.jpg") ;
    ALLEGRO_BITMAP* kennedy = al_load_bitmap("../Bitmap/Menu/kennion.jpg") ;

    ///CREATION DE L'ECRITURE
    ALLEGRO_FONT *font = al_load_ttf_font("../Blomberg-8MKKZ.otf", 70, ALLEGRO_ALIGN_LEFT);
    ALLEGRO_FONT *smallfont = al_load_ttf_font("../Blomberg-8MKKZ.otf", 35, ALLEGRO_ALIGN_LEFT);

    ///CREATION DE LA QUEUE D'EVENEMENT
    queue = al_create_event_queue();
    assert(queue);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(times));
    al_start_timer(times);

    ///INITIALISATION DU JEU
    menu.mode_de_jeu = MENU;
    initJeu(&jeu);
    initBitmapDeco(&menu);


    while (!isFin) {

        ///MENU
        while (menu.mode_de_jeu != JOUER && menu.mode_de_jeu != FIN) {
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_KEY_DOWN : {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_ESCAPE : {
                            menu.mode_de_jeu = FIN;
                            isFin = 1;
                            break;
                        }
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_AXES : {
                    jeu.mouse_x = event.mouse.x;
                    jeu.mouse_y = event.mouse.y;
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    if ((event.mouse.button & 1) == 1) {
                        switch (menu.mode_de_jeu) {
                            case MENU : {
                                if (jeu.mouse_x > 650 && jeu.mouse_x < 1050 && jeu.mouse_y > 400 && jeu.mouse_y < 520) {
                                    jeu.mode = true;
                                    menu.mode_de_jeu = JOUER;
                                }
                                if (jeu.mouse_x > 650 && jeu.mouse_x < 1050 && jeu.mouse_y > 580 && jeu.mouse_y < 700) {
                                    menu.mode_de_jeu = REGLES;
                                }
                                if (jeu.mouse_x > 650 && jeu.mouse_x < 1050 && jeu.mouse_y > 760 && jeu.mouse_y < 880) {
                                    menu.mode_de_jeu = EQUIPE;
                                }
                                break;
                            }
                            case EQUIPE : {
                                if (jeu.mouse_x < 300 && jeu.mouse_x > 20 && jeu.mouse_y < 90 && jeu.mouse_y > 20) {
                                    menu.mode_de_jeu = MENU;
                                }
                                break;
                            }
                            case REGLES : {
                                if (jeu.mouse_x < 300 && jeu.mouse_x > 20 && jeu.mouse_y < 90 && jeu.mouse_y > 20) {
                                    menu.mode_de_jeu = MENU;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
                case ALLEGRO_EVENT_TIMER : {
                    draw = 1;
                    break;
                }
            }
            if (draw) {
                al_draw_scaled_bitmap(background, 0, 0, 1704, 960, 0, 0, width, height, 0);
                switch (menu.mode_de_jeu) {
                    case MENU : {
                        dessinerMenu(font, jeu.mouse_x, jeu.mouse_y);
                        break;
                    }
                    case EQUIPE : {
                        dessinerEquipe(&menu, font, (float) width, (float) height, (float) jeu.mouse_x,
                                       (float) jeu.mouse_y);
                        break;
                    }
                    case REGLES : {
                        dessinerRegles(&menu, font, smallfont,(float) width, (float) height, (float) jeu.mouse_x,
                                       (float) jeu.mouse_y, jeu.habitations[TERRAIN].image, jeu.habitations[CABANE].image, jeu.habitations[MAISON].image,jeu.habitations[IMMEUBLE].image, jeu.habitations[GRATTE_CIEL].image) ;
                    }
                }
                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }

        ///JOUER
        while (menu.mode_de_jeu == JOUER) {
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_KEY_DOWN : {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_ESCAPE : {
                            menu.mode_de_jeu = FIN;
                            isFin = 1;
                            break;
                        }
                        case ALLEGRO_KEY_Z : {
                            jeu.zoom.direction[HAUT] = 1 ;
                            break;
                        }
                        case ALLEGRO_KEY_S : {
                            jeu.zoom.direction[BAS] = 1 ;
                            break;
                        }
                        case ALLEGRO_KEY_D : {
                            jeu.zoom.direction[DROITE] = 1 ;
                            break;
                        }
                        case ALLEGRO_KEY_Q: {
                            jeu.zoom.direction[GAUCHE] = 1 ;
                            break;
                        }
                    }
                    break;
                }
                case ALLEGRO_EVENT_KEY_UP : {
                    for(int i = 0 ; i < 4 ; i++) {
                        jeu.zoom.direction[i] = 0 ;
                    }
                    break ;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    if ((event.mouse.button & 1) == 1) {
                        if (jeu.mode == false) {
                            jeu.mouseIsPressed = true;
                        }
                        else mouseIsPressed = true ;
                    }



                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if ((event.mouse.button & 1) == 1) {
                        if (jeu.mode == false) {
                            jeu.mouseIsPressed = false;
                        }
                        else mouseIsPressed = false ;
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_AXES : {
                    jeu.mouse_x = event.mouse.x;
                    jeu.mouse_y = event.mouse.y;
                    if(event.mouse.dz != 0 && jeu.zoom.CaseX_X + event.mouse.dz >= CASEX_X && jeu.zoom.CaseX_X + event.mouse.dz < 150){
                        jeu.zoom.CaseX_X += 2 * event.mouse.dz ;
                        zoom(&jeu, determinerCaseX(jeu.mouse_x, jeu.zoom.mapX, jeu.zoom.CaseX_X), determinerCaseY(jeu.mouse_y, jeu.zoom.mapX, jeu.zoom.CaseX_X)) ;
                    }
                    break;
                }

                case ALLEGRO_EVENT_TIMER : {
                    deplacerMap(&jeu) ;
                    draw = 1;
                    if(jeu.mode == false) {
                        compteur++;
                        temps(&jeu.time[0], compteur, 0);
                        temps(&jeu.time[1], compteur, 1);
                    }
                    break;
                }
            }
            if (draw) {
                al_draw_scaled_bitmap(menu.deco[6].image, 0, 0, 1704, 960, 0, 0, width, height, 0);
                dessinerJeu(smallfont, font, &jeu);
                if(jeu.mode  == true) {
                    al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150));
                    al_draw_filled_rectangle(550, 150, 1150, 400, al_map_rgb(67, 18, 14));
                    al_draw_rectangle(550, 150, 1150, 400, al_map_rgb(235, 166, 160), 5);
                    al_draw_filled_triangle(980, 160, 750, 390, 980, 390, al_map_rgb(237, 28, 36));
                    al_draw_filled_triangle(560, 390, 740, 390, 740, 160, al_map_rgb(235, 166, 160));
                    al_draw_filled_triangle(740, 390, 740, 160, 970, 160, al_map_rgb(235, 166, 160));
                    al_draw_filled_triangle(650, 250, 560, 160, 970, 160, al_map_rgb(67, 18, 14));
                    al_draw_scaled_bitmap(staline, 0, 0, 463, 647, 980, 160, 160, 230, 1);

                    al_draw_filled_rectangle(550, 500, 1150, 750, al_map_rgb(143, 180, 206));
                    al_draw_rectangle(550, 500, 1150, 750, al_map_rgb(255, 255, 255), 5);
                    al_draw_filled_rectangle(720, 510, 730, 740, al_map_rgb(164, 8, 30));
                    al_draw_filled_triangle(730, 510, 730, 740, 850, 740, al_map_rgb(164, 8, 30));
                    al_draw_filled_triangle(740, 510, 860, 740, 950, 740, al_map_rgb(44, 8, 130));
                    al_draw_filled_triangle(740, 510, 830, 510, 950, 740, al_map_rgb(44, 8, 130));

                    al_draw_scaled_bitmap(kennedy, 0, 0, 800, 1135, 560, 510, 160, 230, 0);
                    al_draw_text(smallfont, al_map_rgb(0, 0,0), 850, 610, ALLEGRO_ALIGN_CENTER, "En cours de developpement") ;

                    if (jeu.mouse_x < 1150 && jeu.mouse_x > 550 && jeu.mouse_y < 400 && jeu.mouse_y > 150) {
                        al_draw_rectangle(550, 150, 1150, 400, al_map_rgb(237, 28, 36), 5);
                        if(mouseIsPressed == true) {
                            jeu.mode = false;
                            jeu.modeJeu = COMMUNISTE;
                        }
                    }
                    if (jeu.mouse_x < 1150 && jeu.mouse_x > 550 && jeu.mouse_y < 750 && jeu.mouse_y > 500) {
                        al_draw_rectangle(550, 500, 1150, 750, al_map_rgb(44, 8, 130), 5);
                        if(mouseIsPressed == true) {
                            jeu.mode = false;
                            jeu.modeJeu = CAPITALISTE;
                        }
                    }
                }


                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }
    }

//    ///DESTRUCTION DES ELEMENTS DU JEU
    return 0;
}
