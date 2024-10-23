#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

bool Done = false;
bool ShowOptions = false;
bool Game = false;

int TileSize = 64;
int TileMap[10][10] = {
    0, 0, 0, 0 , 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1 , 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0 , 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0 , 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0 , 0, 0, 0, 0, 0, 0,
};

enum TileType {
    grass = 0,
    ground = 1,
    Point = 2
};

struct Player {
    ALLEGRO_BITMAP* CurrentPlayer;
    int XPlayerPosition;
    int YPlayerPosition;
    int Speed;
};

bool canMove(int newX, int newY) {

    return true;
}

void GameScreen(ALLEGRO_DISPLAY* Display, ALLEGRO_FONT* Font, ALLEGRO_EVENT event) {
    struct Player Player1;
    Player1.CurrentPlayer = al_load_bitmap("./Assets/sprites/knight.png");
    Player1.XPlayerPosition = 200;
    Player1.YPlayerPosition = 300;
    Player1.Speed = 3;

    struct Player Player2;
    Player2.CurrentPlayer = al_load_bitmap("./Assets/sprites/knight.png");
    Player2.XPlayerPosition = 400;
    Player2.YPlayerPosition = 300;
    Player2.Speed = 3;

    float Frame = 3.f;
    float Current_Frame_Y = 53;
    char Score_Text[50] = { 0 };

    bool redraw = true;
    bool keys[ALLEGRO_KEY_MAX] = { false };

    // Desenhar o cenário
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int x = j * TileSize;
            int y = i * TileSize;

            if (TileMap[i][j] == grass) {
                al_draw_filled_rectangle(x, y, x + TileSize, y + TileSize, al_map_rgb(0, 255, 0));
            }
            else if (TileMap[i][j] == ground) {
                al_draw_filled_rectangle(x, y, x + TileSize, y + TileSize, al_map_rgb(139, 69, 19));
            }
        }
    }

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        Done = true;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        keys[event.keyboard.keycode] = true;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        keys[event.keyboard.keycode] = false;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
        
        int Player1newX = Player1.XPlayerPosition;
        int Player1newY = Player1.YPlayerPosition;
        int Player2newX = Player2.XPlayerPosition;
        int Player2newY = Player2.YPlayerPosition;

        if (keys[ALLEGRO_KEY_W]) { // Move para cima
            Player1newY -= Player1.Speed;
        }
        if (keys[ALLEGRO_KEY_S]) { // Move para baixo
            Player1newY += Player1.Speed;
        }
        if (keys[ALLEGRO_KEY_A]) { // Move para esquerda
            Player1newX -= Player1.Speed;
        }
        if (keys[ALLEGRO_KEY_D]) { // Move para direita
            Player1newX += Player1.Speed;
        }

        // Verifica se pode mover para a nova posição
        if (canMove(Player1newX, Player1newY)) {
            Player1.XPlayerPosition = Player1newX;
            Player1.YPlayerPosition = Player1newY;
        }
        else {
            printf_s("Não é possível mover para a tile de grama.\n");
        }

        if (keys[ALLEGRO_KEY_I]) {
            Player2newY -= Player2.Speed;
        }
        if (keys[ALLEGRO_KEY_K]) {
            Player2newY += Player2.Speed;
        }
        if (keys[ALLEGRO_KEY_J]) {
            Player2newX -= Player2.Speed;
        }
        if (keys[ALLEGRO_KEY_L]) {
            Player2newX += Player2.Speed;
        }
        if (canMove(Player2newX, Player2newY)) {
            Player2.XPlayerPosition = Player2newX;
            Player2.YPlayerPosition = Player2newY;
        }
        else {
            printf_s("Não é possível mover para a tile de grama.\n");
        }
        al_draw_bitmap_region(Player1.CurrentPlayer, 32 * (int)Frame, Current_Frame_Y, 32, 53, Player1.XPlayerPosition, Player1.YPlayerPosition, 0);
        al_draw_bitmap_region(Player2.CurrentPlayer, 32 * (int)Frame, Current_Frame_Y, 32, 53, Player2.XPlayerPosition, Player2.YPlayerPosition, 0);
        al_draw_text(Font, al_map_rgb(0, 0, 0), 30, 30, 0, Score_Text);

        al_flip_display();
        al_rest(0.01);
    }
}




void OptionsScreen(ALLEGRO_DISPLAY* Display, ALLEGRO_FONT* Font, ALLEGRO_BITMAP* BackGroundImage, int BgWidth, int BgHeight) {
    al_draw_scaled_bitmap(BackGroundImage, 0, 0, BgWidth, BgHeight, 0, 0, 800, 600, 0);
    //al_draw_rectangle(BgWidth / 2, 480, 300, 430, al_map_rgb(255, 0, 0), 0);
    al_flip_display();
}

void StartScreen(ALLEGRO_DISPLAY* Display, ALLEGRO_FONT* Font, ALLEGRO_BITMAP* BackGroundImage, int BgWidth, int BgHeight) {
    al_draw_scaled_bitmap(BackGroundImage, 0, 0, BgWidth, BgHeight, 0, 0, 800, 600, 0);
    /*al_draw_rectangle(BgWidth / 2, 355, 300, 320, al_map_rgb(255, 0, 0), 0);
    al_draw_rectangle(BgWidth / 2, 420, 300, 370, al_map_rgb(255, 0, 0), 0);
    al_draw_rectangle(BgWidth / 2, 470, 300, 430, al_map_rgb(255, 0, 0), 0);*/
    al_flip_display();
}

int main() {
    al_init();
    al_init_font_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_mouse();

    ALLEGRO_DISPLAY* Display = al_create_display(800, 600);
    al_set_window_position(Display, 200, 200);


    ALLEGRO_FONT* Font = al_create_builtin_font();
    ALLEGRO_TIMER* Timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_BITMAP* StartScreenBackGround = al_load_bitmap("./Assets/LoadingPage2.png");
    ALLEGRO_BITMAP* OptionsBackGround = al_load_bitmap("./Assets/SettingsPage.png");
    ALLEGRO_EVENT_QUEUE* EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_display_event_source(Display));
    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_timer_event_source(Timer));
    al_register_event_source(EventQueue, al_get_mouse_event_source());

    al_start_timer(Timer);

    int BgWidth = al_get_bitmap_width(StartScreenBackGround);
    int BgHeight = al_get_bitmap_height(StartScreenBackGround);
    int OptionsBgWidth = al_get_bitmap_width(OptionsBackGround);
    int OptionsBgHeight = al_get_bitmap_height(OptionsBackGround);


    bool Once = true;

    while (!Done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(EventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            Done = true;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            Done = true;
        }

        if (ShowOptions) {
            OptionsScreen(Display, Font, OptionsBackGround, OptionsBgWidth, OptionsBgHeight);
        }
        else if (Game) {

            if (Once) {
                Display = al_create_display(640, 480);
                GameScreen(Display, Font, event);
                Once = false;
            }



        }
        else {
            StartScreen(Display, Font, StartScreenBackGround, BgWidth, BgHeight);
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
            float y1 = 320;
            float y2 = 370;
            float y3 = 430;
            float backButtonY = 480;

            if (!Game) {
                if (ShowOptions) {
                    if (event.mouse.y >= 430 && event.mouse.y <= backButtonY) {
                        ShowOptions = false;
                    }
                }
                else {

                    if (event.mouse.y >= y1 && event.mouse.y <= 355) {
                        Game = true;
                    }

                    // Botão de Opções
                    if (event.mouse.y >= y2 && event.mouse.y <= 420) {
                        ShowOptions = true;
                    }


                    if (event.mouse.y >= y3 && event.mouse.y <= 470) {
                        Done = true;
                    }
                }
            }
        }
    }

    // Limpeza de recursos
    al_destroy_display(Display);
    al_destroy_font(Font);
    al_destroy_event_queue(EventQueue);
    al_destroy_timer(Timer);
    al_destroy_bitmap(StartScreenBackGround);
    al_destroy_bitmap(OptionsBackGround);

    return 0;
}