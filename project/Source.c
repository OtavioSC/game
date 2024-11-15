#include <stdio.h>  
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int countdown_time = 50;
int main() {

    al_init();
    al_init_font_addon();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY* Display = al_create_display(1200, 880);
    al_set_window_position(Display, 200, 200);

    // ALLEGRO_FONT* Font = al_load_font("/home/otso/.local/share/fonts/Poppins/Poppins-Medium.ttf", 36, 0);
    ALLEGRO_FONT* Font = al_create_builtin_font();
    ALLEGRO_TIMER* Timer = al_create_timer(1.0 / 25.0);
    ALLEGRO_TIMER* Countdown_timer = al_create_timer(1.0);

    ALLEGRO_BITMAP* Sprite = al_load_bitmap("./Assets/sprites/dog.png");
    ALLEGRO_BITMAP* CatSprite = al_load_bitmap("./Assets/sprites/cat.png");
    ALLEGRO_EVENT_QUEUE* EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_display_event_source(Display));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_timer_event_source(Timer));
    al_register_event_source(EventQueue, al_get_timer_event_source(Countdown_timer));

    al_start_timer(Timer);
    al_start_timer(Countdown_timer);

    float frame = 0.f;
    float cat_frame = 0.f;
    float PositionX = 200;
    float PositionY = 200;
    float cat_position_x= 300;
    float cat_position_y= 300;
    float cat_current_frame_y = 160;
    float current_frame_y = 160;
    int Score = 0;
    char Score_Text[50] = { 0 };
    char Countdown_Text[50] = { 0 };
    bool key[4] = { false, false, false, false};
    bool cat_key[4] = { false, false, false, false};

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(EventQueue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            if (key[0] && PositionY >= 100){
                frame += 0.3f;
                current_frame_y = 32 * 2;
                PositionY -= 3;
            }
           if (key[1] && PositionY <= 400) {
                frame += 0.3f;
                current_frame_y = 32 * 4;
                PositionY += 3;
           }
            if (key[2] && PositionX >= 100) {
                frame += 0.3f;
                current_frame_y = 32 * 9;
                PositionX -= 3;
            }
            if (key[3] && PositionX <= 500) {
                frame += 0.3f;
                current_frame_y = 32 * 8;
                PositionX += 3;
            }

            if (cat_key[0] && cat_position_y >= 100){
                cat_frame += 0.3f;
                cat_current_frame_y = 32 * 2;
                cat_position_y -= 3;
            }
           if (cat_key[1] && cat_position_y <= 400) {
                cat_frame += 0.3f;
                cat_current_frame_y = 0;
                cat_position_y += 3;
           }
            if (cat_key[2] && cat_position_x >= 100) {
                cat_frame += 0.3f;
                cat_current_frame_y = 32 * 3;
                cat_position_x -= 3;
            }
            if (cat_key[3] && cat_position_x <= 500) {
                cat_frame += 0.3f;
                cat_current_frame_y = 32;
                cat_position_x += 3;
            }

            if (event.timer.source == Countdown_timer) {
                countdown_time--;
                if (countdown_time <= 0) {
                    break;
                }
            }
        }

        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) { 
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    key[0] = false;
                    break;
                case ALLEGRO_KEY_S:
                    key[1] = false;
                    break;
                case ALLEGRO_KEY_A:
                    key[2] = false;
                    break;
                case ALLEGRO_KEY_D:
                    key[3] = false;
                    break;
                case ALLEGRO_KEY_I:
                    cat_key[0] = false;
                    break;
                case ALLEGRO_KEY_K:
                    cat_key[1] = false;
                    break;
                case ALLEGRO_KEY_J:
                    cat_key[2] = false;
                    break;
                case ALLEGRO_KEY_L:
                    cat_key[3] = false;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {  
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    key[0] = true;
                    break;
                case ALLEGRO_KEY_S:
                    key[1] = true;
                    break;
                case ALLEGRO_KEY_A:
                    key[2] = true;
                    break;
                case ALLEGRO_KEY_D:
                    key[3] = true;
                    break;
                case ALLEGRO_KEY_I:
                    cat_key[0] = true;
                    break;
                case ALLEGRO_KEY_K:
                    cat_key[1] = true;
                    break;
                case ALLEGRO_KEY_J:
                    cat_key[2] = true;
                    break;
                case ALLEGRO_KEY_L:
                    cat_key[3] = true;
                    break;
            }
        Score++;
             
        }

        if (frame > 3) {
            frame -= 3;
        }

        if (cat_frame > 3) {
            cat_frame -= 3;
        }

        snprintf(Score_Text, sizeof(Score_Text), "Score: %d", Score);
        snprintf(Countdown_Text, sizeof(Countdown_Text), "Timer: %d", countdown_time);
        al_clear_to_color(al_map_rgb(100, 100, 100));
        al_draw_text(Font, al_map_rgb(0, 0, 0), 30, 50, 0,  Countdown_Text);
        al_draw_bitmap_region(Sprite, 32 * (int)frame, current_frame_y, 32, 32, PositionX, PositionY, 0);
        al_draw_bitmap_region(CatSprite, 32 * (int)cat_frame, cat_current_frame_y, 32, 32, cat_position_x, cat_position_y, 0);
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
