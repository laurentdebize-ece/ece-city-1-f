#include "menu.h"
#include "jeu.h"
#include "time.h"

#include <stdio.h>

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
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    ///CREATION DES DONNEES DU JEU
    int isFin = 0, draw = 0, compteur = 0;
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
    menu.deco[4].image = al_load_bitmap("../Bitmap/map.png");


    jeu.icone[0].image = al_load_bitmap("../Bitmap/Icone/habitant.png");
    jeu.icone[1].image = al_load_bitmap("../Bitmap/Icone/outil.png");
    jeu.icone[2].image = al_load_bitmap("../Bitmap/Icone/route.png");
    jeu.icone[3].image = al_load_bitmap("../Bitmap/Icone/maison.png");
    jeu.icone[4].image = al_load_bitmap("../Bitmap/Icone/chateau_eau.png");
    jeu.icone[5].image = al_load_bitmap("../Bitmap/Icone/EclairOk-removebg-preview.png");
    jeu.icone[6].image = al_load_bitmap("../Bitmap/Icone/IconeEau-removebg-preview.png");
    jeu.icone[7].image = al_load_bitmap("../Bitmap/Icone/coins.png");
    jeu.icone[8].image = al_load_bitmap("../Bitmap/Icone/SIMCITYECE.png");
    jeu.icone[9].image = al_load_bitmap("../Bitmap/Icone/CaptureIconeEcole-removebg-preview.png");
    jeu.icone[10].image = al_load_bitmap("../Bitmap/Icone/PetitEcolier3-removebg-preview.png");



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
    ALLEGRO_BITMAP* chateau = al_load_bitmap("../Bitmap/Batiments/chateau_eau.png") ;





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
                al_draw_bitmap(background, 0, 0, 0);
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
                        al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150));
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
                        jeu.mouseIsPressed = true;
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if ((event.mouse.button & 1) == 1) {
                        jeu.mouseIsPressed = false;
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_AXES : {
                    jeu.mouse_x = event.mouse.x;
                    jeu.mouse_y = event.mouse.y;
                    if(event.mouse.dz != 0 && jeu.zoom.CaseX_X + event.mouse.dz >= 25 && jeu.zoom.CaseX_X + event.mouse.dz < 150){
                        jeu.zoom.CaseX_X += 2 * event.mouse.dz ;
                        zoom(&jeu, determinerCaseX(jeu.mouse_x, jeu.zoom.mapX, jeu.zoom.CaseX_X), determinerCaseY(jeu.mouse_y, jeu.zoom.mapX, jeu.zoom.CaseX_X)) ;
                    }
                    break;
                }

                case ALLEGRO_EVENT_TIMER : {
                    deplacerMap(&jeu) ;

                    draw = 1;
                    compteur++;
                    temps(&jeu.time[0], compteur, 0);
                    temps(&jeu.time[1], compteur, 1);
                    break;
                }
            }
            if (draw) {
                al_draw_bitmap(menu.deco[4].image, 0, 0, 0);
                dessinerJeu(smallfont, font, &jeu);
                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }
    }

//    ///DESTRUCTION DES ELEMENTS DU JEU
    return 0;
}
