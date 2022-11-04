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
    display = al_create_display(1150, 900);
    double height = al_get_display_height(display);
    double width = al_get_display_width(display);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "ECE SimCity") ;

    ///COULEUR
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    ///CREATION DES DONNEES DU JEU
    int isFin = 0, draw = 0;
    int mouse_x = 0, mouse_y = 0, compteur = 0;
    times = al_create_timer(0.02);
    Menu menu;
    Jeu jeu ;
    initJeu(&jeu) ;


    ///CREATION DES IMAGES
    ALLEGRO_BITMAP* background = al_load_bitmap("../Bitmap/backgroundMenu.jpg") ;
    menu.batimentDeco[0] = al_load_bitmap("../Bitmap/bat1.png") ;
    menu.batimentDeco[1] = al_load_bitmap("../Bitmap/bat2.png") ;
    menu.batimentDeco[2] = al_load_bitmap("../Bitmap/bat3.png") ;
    menu.batimentDeco[3] = al_load_bitmap("../Bitmap/bat4.png") ;
    menu.batimentDeco[4] = al_load_bitmap("../Bitmap/bat5.png") ;
    menu.batimentDeco[5] = al_load_bitmap("../Bitmap/bat6.png") ;
    menu.batimentDeco[6] = al_load_bitmap("../Bitmap/fares.png") ;
    menu.batimentDeco[7] = al_load_bitmap("../Bitmap/valentin.png") ;
    ALLEGRO_BITMAP* habitant = al_load_bitmap("../Bitmap/habitant.png") ;

    ///CREATION DE L'ECRITURE
    ALLEGRO_FONT* font = al_load_ttf_font("../Blomberg-8MKKZ.otf", 50, ALLEGRO_ALIGN_LEFT) ;
    ALLEGRO_FONT* smallfont = al_load_ttf_font("../Blomberg-8MKKZ.otf", 25, ALLEGRO_ALIGN_LEFT) ;



    queue = al_create_event_queue();
    assert(queue);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(times));
    al_start_timer(times);
    menu.mode_de_jeu = MENU ;
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
                    mouse_x = event.mouse.x;
                    mouse_y = event.mouse.y;
                    break;
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                    if ((event.mouse.button & 1) == 1) {
                        switch (menu.mode_de_jeu) {
                            case MENU : {
                                if (mouse_x > 422 && mouse_x < 728 && mouse_y > 400 && mouse_y < 480) {
                                    menu.mode_de_jeu = JOUER;
                                }
                                if (mouse_x > 422 && mouse_x < 728 && mouse_y > 530 && mouse_y < 610) {
                                    menu.mode_de_jeu = REGLES;
                                }
                                if (mouse_x > 422 && mouse_x < 728 && mouse_y > 660 && mouse_y < 740) {
                                    menu.mode_de_jeu = EQUIPE;
                                }
                                break;
                            }
                            case EQUIPE : {
                                if (mouse_x < 170 && mouse_x > 10 && mouse_y < 70 && mouse_y > 10) {
                                    menu.mode_de_jeu = MENU;
                                }
                                break;
                            }
                            case REGLES : {
                                if (mouse_x < 170 && mouse_x > 10 && mouse_y < 70 && mouse_y > 10) {
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
                al_draw_scaled_bitmap(background, 0, 0, 1024, 767, 0, 0, width, height, 0);
                switch (menu.mode_de_jeu) {
                    case MENU : {
                        dessinerMenu(font, mouse_x, mouse_y);
                        break;
                    }
                    case EQUIPE : {
                        dessinerEquipe(&menu, font, (float)width, (float)height, (float)mouse_x, (float)mouse_y) ;
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
                case ALLEGRO_EVENT_TIMER : {
                        draw = 1;
                        compteur++ ;
                        temps(&jeu.time, compteur) ;
                        break ;
                }
            }
            if (draw) {
                dessinerJeu(smallfont, jeu, width, height) ;
                al_draw_scaled_bitmap(habitant, 0, 0, 1024, 985, 1000, 3, 40, 30, 0) ;
                al_draw_textf(smallfont, al_map_rgb(255, 255, 255), 980, 7, ALLEGRO_ALIGN_CENTER, "%d", jeu.nbHabitants) ;
                al_flip_display();
                al_clear_to_color(black);
                draw = 0;
            }
        }
    }

    ///DESTRUCTION DES ELEMENTS DU JEU
    return 0;
}