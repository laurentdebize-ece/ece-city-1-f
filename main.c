#include <stdio.h>
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
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ///CREATION DU DISPLAY
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(1024, 768);
    double height = al_get_display_height(display);
    double width = al_get_display_width(display);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "ECE SimCity") ;

    ///COULEUR
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    ///CREATION DES DONNEES DU JEU
    int isFin = 0, draw = 0, compteur = 0;
    times = al_create_timer(0.02);
    Menu menu;
    Jeu jeu ;

    ///CHARGEMENT DES IMAGES

    ALLEGRO_BITMAP* background = al_load_bitmap("../Bitmap/Menu/backgroundMenu.jpg") ;
    menu.deco[0].image = al_load_bitmap("../Bitmap/Menu/bat3.png") ;
    menu.deco[1].image = al_load_bitmap("../Bitmap/Menu/bat4.png") ;
    menu.deco[2].image = al_load_bitmap("../Bitmap/Photo/fares.png") ;
    menu.deco[3].image = al_load_bitmap("../Bitmap/Photo/valentin.png") ;
    menu.deco[4].image = al_load_bitmap("../Bitmap/map.png") ;


    jeu.icone[0].image = al_load_bitmap("../Bitmap/Icone/habitant.png") ;
    jeu.icone[1].image = al_load_bitmap("../Bitmap/Icone/outil.png") ;
    jeu.icone[2].image = al_load_bitmap("../Bitmap/Icone/route.png") ;



    ///CREATION DE L'ECRITURE
    ALLEGRO_FONT* font = al_load_ttf_font("../Blomberg-8MKKZ.otf", 50, ALLEGRO_ALIGN_LEFT) ;
    ALLEGRO_FONT* smallfont = al_load_ttf_font("../Blomberg-8MKKZ.otf", 25, ALLEGRO_ALIGN_LEFT) ;


    ///CREATION DE LA QUEUE D'EVENEMENT
    queue = al_create_event_queue();
    assert(queue);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(times));
    al_start_timer(times);

    ///INITIALISATION DU JEU
    menu.mode_de_jeu = MENU    ;
    initJeu(&jeu) ;
    initBitmapDeco(&menu) ;


    while (!isFin) {
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
                                if (jeu.mouse_x > 357 && jeu.mouse_x < 662 && jeu.mouse_y > 300 && jeu.mouse_y < 380) {
                                    menu.mode_de_jeu = JOUER;
                                }
                                if (jeu.mouse_x > 357 && jeu.mouse_x < 662 && jeu.mouse_y > 430 && jeu.mouse_y < 510) {
                                    menu.mode_de_jeu = REGLES;
                                }
                                if (jeu.mouse_x > 357 && jeu.mouse_x < 662 && jeu.mouse_y > 560 && jeu.mouse_y < 640) {
                                    menu.mode_de_jeu = EQUIPE;
                                }
                                break;
                            }
                            case EQUIPE : {
                                if (jeu.mouse_x < 170 && jeu.mouse_x > 10 && jeu.mouse_y < 70 && jeu.mouse_y > 10) {
                                    menu.mode_de_jeu = MENU;
                                }
                                break;
                            }
                            case REGLES : {
                                if (jeu.mouse_x < 170 && jeu.mouse_x > 10 && jeu.mouse_y < 70 && jeu.mouse_y > 10) {
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
                    break ;
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
                        dessinerEquipe(&menu, font, (float)width, (float)height, (float)jeu.mouse_x, (float)jeu.mouse_y) ;
                        break;
                    }
                    case REGLES : {
                        al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150)) ;
                    }
                }
                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }
        while(menu.mode_de_jeu == JOUER) {
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
                    break ;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    if ((event.mouse.button & 1) == 1) {
                        jeu.mouseIsPressed = true ;
                    }
                    break ;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                    if ((event.mouse.button & 1) == 1) {
                        jeu.mouseIsPressed = false ;
                    }
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_AXES : {
                    jeu.mouse_x = event.mouse.x;
                    jeu.mouse_y = event.mouse.y;
                    break;
                }
                case ALLEGRO_EVENT_TIMER : {
                        draw = 1;
                        compteur++ ;
                        temps(&jeu.time, compteur) ;
                        break ;
                }
            }
            if (draw) {
                al_draw_bitmap(menu.deco[4].image, -20, -55, 0) ;
                dessinerJeu(smallfont, font, &jeu) ;
                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }
    }

    ///DESTRUCTION DES ELEMENTS DU JEU
    return 0;
}