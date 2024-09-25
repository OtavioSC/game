#include <stdio.h>  
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {

    al_init();
    al_init_font_addon();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY* Display = al_create_display(640, 480);
    al_set_window_position(Display, 200, 200);

    ALLEGRO_FONT* Font = al_create_builtin_font();
    ALLEGRO_TIMER* Timer = al_create_timer(1.0 / 30.0);

    ALLEGRO_BITMAP* Sprite = al_load_bitmap("./Assets/sprites/knight.png");

    ALLEGRO_EVENT_QUEUE* EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_display_event_source(Display));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_timer_event_source(Timer));
    al_start_timer(Timer);

    float Frame = 3.f;
    float PositionX = 200;
    float PositionY = 200;
    float Current_Frame_Y = 53;
    int Score = 0;
    char Score_Text[50] = { 0 };

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(EventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {  
            if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                PositionY -= 1;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                PositionY += 1;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                PositionX += 1;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                PositionX -= 1;
            }
        Score++;
             
        }

        Frame += 0.3;
        if (Frame > 8) {
            Frame = 3;
        }

        
        snprintf(Score_Text, sizeof(Score_Text), "Score: %d", Score);

        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_bitmap_region(Sprite, 32 * (int)Frame, Current_Frame_Y, 32, 53, PositionX, PositionY, 0);
        al_draw_text(Font, al_map_rgb(0, 0, 0), 30, 30, 0, Score_Text);
        al_flip_display();

        
        al_rest(0.01);
    }

    al_destroy_display(Display);
    al_destroy_font(Font);
    al_destroy_event_queue(EventQueue);
    al_destroy_timer(Timer);
    al_destroy_bitmap(Sprite);

    return 0;
}
