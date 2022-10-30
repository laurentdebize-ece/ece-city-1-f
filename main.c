#include <stdio.h>
#include "menu.h"

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
    int isFin = 0, draw = 0;
    int mouse_x = 0, mouse_y = 0;
    times = al_create_timer(0.02);
    Menu menu;
    int rect1 = 0, rect2 = 0, rect3 = 0 ;

    ALLEGRO_BITMAP* background = al_load_bitmap("../backgroundMenu.jpg") ;
    ALLEGRO_FONT* font = al_load_ttf_font("../Blomberg-8MKKZ.otf", 50, ALLEGRO_ALIGN_LEFT) ;

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
                                if (mouse_x > 357 && mouse_x < 662 && mouse_y > 300 && mouse_y < 380) {
                                    menu.mode_de_jeu = JOUER;
                                }
                                if (mouse_x > 357 && mouse_x < 662 && mouse_y > 430 && mouse_y < 510) {
                                    menu.mode_de_jeu = REGLES;
                                }
                                if (mouse_x > 357 && mouse_x < 662 && mouse_y > 560 && mouse_y < 640) {
                                    menu.mode_de_jeu = EQUIPE;
                                }
                                break;
                            }
                            case EQUIPE : {
                                break;
                            }
                            case REGLES : {
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
                        dessinerMenu(font, mouse_x, mouse_y);
                        break;
                    }
                    case EQUIPE : {
                        al_draw_filled_rectangle(0, 0, width, height, al_map_rgba(150, 150, 150, 150)) ;
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
                        break ;
                }
            }
            if (draw) {
                al_draw_text(font, black, 507, 360, ALLEGRO_ALIGN_CENTER, "valentin ntm");
                al_flip_display();
                al_clear_to_color(white);
                draw = 0;
            }
        }
    }

    ///DESTRUCTION DES ELEMENTS DU JEU
    return 0;
}