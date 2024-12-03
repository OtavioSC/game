#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <stdio.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 880
#define BORDER_WIDTH 250
#define BORDER_HEIGHT 170

bool game_running = true;
bool bIsEndGame = false;
bool bIsGame = false;
bool bIsMenu = true;
bool bIsOptions = false;
bool bIsPlaySound = true;
bool bIsTutorial = false;
int countdown_time = 45;

ALLEGRO_SAMPLE *Sample = NULL;

typedef struct {
  int operand1;
  int operand2;
  char operator;
  int result;
} Question;

Question generate_question() {
  Question q;
  q.operand1 = rand() % 9 + 1;
  q.operand2 = rand() % 9 + 1;
  int op = rand() % 3;
  switch (op) {
  case 0:
    q.operator= '+';
    q.result = q.operand1 + q.operand2;
    break;
  case 1:
    q.operator= '-';
    q.result = q.operand1 - q.operand2;
    break;
  case 2:
    q.operator= '*';
    q.result = q.operand1 * q.operand2;
    break;
  }
  return q;
}
void initMusic() {
  if (Sample == NULL) {
    Sample = al_load_sample("./Assets/music/8bit.ogg");
  }
}
void playMusic() {
  if (Sample && bIsPlaySound)
    al_play_sample(Sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void stopMusic() {
  if (Sample)
    al_destroy_sample(Sample);
}

int main() {
  al_init();
  al_init_font_addon();
  al_install_keyboard();
  al_init_image_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(1);
  al_install_mouse();

  ALLEGRO_DISPLAY *Display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
  al_set_window_position(Display, 200, 200);

  ALLEGRO_FONT *Font =
      al_load_font("./Assets/fonts/PixelOperator8-Bold.ttf", 21, 0);
  // ALLEGRO_FONT* Font = al_create_builtin_font();
  ALLEGRO_TIMER *Timer = al_create_timer(1.0 / 25.0);
  ALLEGRO_TIMER *Countdown_timer = al_create_timer(1.0);

  ALLEGRO_BITMAP *Sprite = al_load_bitmap("./Assets/sprites/dog.png");
  ALLEGRO_BITMAP *CatSprite = al_load_bitmap("./Assets/sprites/cat.png");
  ALLEGRO_BITMAP *Menubackground = al_load_bitmap("./Assets/MenuScreen.png");
  ALLEGRO_BITMAP *Gamebackground = al_load_bitmap("./Assets/background.png");
  ALLEGRO_BITMAP *Optionsbackground =
      al_load_bitmap("./Assets/SettingsScreen.png");
  ALLEGRO_BITMAP *Tutorialbackground =
      al_load_bitmap("./Assets/TutorialScreen.png");
  ALLEGRO_BITMAP *question_bg = al_load_bitmap("./Assets/question.png");
  ALLEGRO_BITMAP *hud = al_load_bitmap("./Assets/hud.png");
  ALLEGRO_BITMAP *menu = al_load_bitmap("./Assets/menu.png");
  ALLEGRO_BITMAP *options = al_load_bitmap("./Assets/settings.png");

  ALLEGRO_EVENT_QUEUE *EventQueue = al_create_event_queue();
  al_register_event_source(EventQueue, al_get_display_event_source(Display));
  al_register_event_source(EventQueue, al_get_keyboard_event_source());
  al_register_event_source(EventQueue, al_get_timer_event_source(Timer));
  al_register_event_source(EventQueue,
                           al_get_timer_event_source(Countdown_timer));
  al_register_event_source(EventQueue, al_get_mouse_event_source());

  srand(time(NULL));
  bool number_active = true;
  bool number_active2 = true;
  float number_x = 600;
  float number_y = 440;
  float number_x2 = 800;
  float number_y2 = 240;
  float frame = 0.f;
  float cat_frame = 0.f;
  float PositionX = 500;
  float PositionY = 500;
  float cat_position_x = 300;
  float cat_position_y = 300;
  float cat_current_frame_y = 320;
  float current_frame_y = 320;
  int Score = 0;
  int random_number2 = rand() % 9 + 1;
  char Score_Text[50] = {0};
  char Countdown_Text[10] = {0};
  bool key[4] = {false, false, false, false};
  bool cat_key[4] = {false, false, false, false};
  bool show_score_screen = false;

  Question current_question = generate_question();
  int random_number = current_question.operand2;

  initMusic();
  playMusic();
  al_start_timer(Timer);
  al_start_timer(Countdown_timer);
  while (game_running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(EventQueue, &event);

    if (bIsMenu) {

      if (event.type == ALLEGRO_EVENT_TIMER) {
        al_draw_bitmap(Menubackground, 0, 0, 0);
        al_flip_display();
      }
      if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
          event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        bIsMenu = false;
        game_running = false;
      }
      if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
          event.mouse.button == 1) {

        if (event.mouse.y >= 440 && event.mouse.y <= 520 &&
            event.mouse.x >= 450 && event.mouse.x <= 750) {
          bIsMenu = false;
          bIsTutorial = true;
        }

        if (event.mouse.y >= 540 && event.mouse.y <= 600 &&
            event.mouse.x >= 450 && event.mouse.x <= 750) {
          game_running = false;
        }

        if (event.mouse.y >= 100 && event.mouse.y <= 200 &&
            event.mouse.x >= 1060 && event.mouse.x <= 1150) {
          bIsMenu = false;
          bIsOptions = true;
        }
      }
    }

    if (bIsOptions) {

      if (event.type == ALLEGRO_EVENT_TIMER) {
        al_draw_bitmap(Optionsbackground, 0, 0, 0);
        al_flip_display();
      }
      if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
          event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        bIsOptions = false;
        game_running = false;
      }
      if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
          event.mouse.button == 1) {

        if (event.mouse.y >= 600 && event.mouse.y <= 670 &&
            event.mouse.x >= 450 && event.mouse.x <= 750) {
          bIsMenu = true;
          bIsOptions = false;
        } else if (event.mouse.y >= 330 && event.mouse.y <= 600 &&
                   event.mouse.x >= 150 && event.mouse.x <= 550) {
                    if (!bIsPlaySound) {
                      bIsPlaySound = true;
                      Sample = al_load_sample("./Assets/music/8bit.ogg");
                      al_play_sample(Sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
                    }
        } else if (event.mouse.y >= 300 && event.mouse.y <= 500 &&
                   event.mouse.x >= 700 && event.mouse.x <= 1000) {
                    if (bIsPlaySound) {
                        stopMusic();
                        bIsPlaySound = false;
                    }
        }
      }
    }
    if (bIsTutorial) {
      bIsMenu = false;
      if (event.type == ALLEGRO_EVENT_TIMER) {
        al_draw_bitmap(Tutorialbackground, 100, 80, 0);
        al_flip_display();
      }
      if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
          event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        bIsTutorial = false;
        game_running = false;
      }
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
        event.mouse.button == 1) {
      if (event.mouse.y >= 700 && event.mouse.y <= 800 &&
          event.mouse.x >= 180 && event.mouse.x <= 400) {
        bIsTutorial = false;
        bIsMenu = false;
        bIsGame = true;
      }
    }
    if (bIsGame) {

      if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
          event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        break;
      }

      if (event.type == ALLEGRO_EVENT_TIMER) {
        cat_current_frame_y = 64 * 7;
        current_frame_y = 64 * 6;
        if (key[0] && PositionY >= BORDER_HEIGHT) {
          frame += 0.3f;
          current_frame_y = 64 * 2;
          PositionY -= 5;
        }
        if (key[1] && PositionY <= (SCREEN_HEIGHT - BORDER_HEIGHT) - 50) {
          frame += 0.3f;
          current_frame_y = 64 * 4;
          PositionY += 5;
        }
        if (key[2] && PositionX >= BORDER_WIDTH) {
          frame += 0.3f;
          current_frame_y = 64 * 9;
          PositionX -= 5;
        }
        if (key[3] && PositionX <= (SCREEN_WIDTH - BORDER_WIDTH) - 64) {
          frame += 0.3f;
          current_frame_y = 64 * 8;
          PositionX += 5;
        }
        if (cat_key[0] && cat_position_y >= BORDER_HEIGHT) {
          cat_frame += 0.3f;
          cat_current_frame_y = 64 * 2;
          cat_position_y -= 5;
        }
        if (cat_key[1] &&
            cat_position_y <= (SCREEN_HEIGHT - BORDER_HEIGHT) - 56) {
          cat_frame += 0.3f;
          cat_current_frame_y = 0;
          cat_position_y += 5;
        }
        if (cat_key[2] && cat_position_x >= BORDER_WIDTH) {
          cat_frame += 0.3f;
          cat_current_frame_y = 64 * 3;
          cat_position_x -= 5;
        }
        if (cat_key[3] &&
            cat_position_x <= (SCREEN_WIDTH - BORDER_WIDTH) - 64) {
          cat_frame += 0.3f;
          cat_current_frame_y = 64;
          cat_position_x += 5;
        }

        bool dog_collision =
            PositionX < number_x + 20 && PositionX + 64 > number_x &&
            PositionY < number_y + 20 && PositionY + 64 > number_y;
        bool cat_collision =
            cat_position_x < number_x + 20 && cat_position_x + 64 > number_x &&
            cat_position_y < number_y + 20 && cat_position_y + 64 > number_y;
        bool dog_collision2 =
            PositionX < number_x2 + 20 && PositionX + 64 > number_x2 &&
            PositionY < number_y2 + 20 && PositionY + 72 > number_y2;
        bool cat_collision2 = cat_position_x < number_x2 + 20 &&
                              cat_position_x + 64 > number_x2 &&
                              cat_position_y < number_y2 + 20 &&
                              cat_position_y + 64 > number_y2;

        if (number_active && (dog_collision || cat_collision)) {
          if (current_question.operand2 == random_number) {
            Score++;
            current_question = generate_question();
            random_number = rand() % 9 + 1;
            random_number2 = current_question.operand2;
            number_x2 = BORDER_WIDTH + rand() % ((SCREEN_WIDTH - BORDER_WIDTH) -
                                                 64 - BORDER_WIDTH + 1);
            number_y2 =
                BORDER_HEIGHT + rand() % ((SCREEN_HEIGHT - BORDER_HEIGHT) - 25 -
                                          BORDER_HEIGHT + 1);
          } else {
            if (Score > 0) {
              Score--;
            }
            current_question = generate_question();
            random_number2 = current_question.operand2;
            random_number = rand() % 9 + 1;
          }
          number_x = BORDER_WIDTH + rand() % ((SCREEN_WIDTH - BORDER_WIDTH) -
                                              64 - BORDER_WIDTH + 1);
          number_y = BORDER_HEIGHT + rand() % ((SCREEN_HEIGHT - BORDER_HEIGHT) -
                                               25 - BORDER_HEIGHT + 1);
        }

        if (number_active2 && (dog_collision2 || cat_collision2)) {
          if (current_question.operand2 == random_number2) {
            Score++;
            current_question = generate_question();
            random_number2 = rand() % 9 + 1;
            random_number = current_question.operand2;
            number_x = BORDER_WIDTH + rand() % ((SCREEN_WIDTH - BORDER_WIDTH) -
                                                64 - BORDER_WIDTH + 1);
            number_y =
                BORDER_HEIGHT + rand() % ((SCREEN_HEIGHT - BORDER_HEIGHT) - 25 -
                                          BORDER_HEIGHT + 1);
          } else {
            if (Score > 0) {
              Score--;
            }
            current_question = generate_question();
            random_number = current_question.operand2;
            random_number2 = rand() % 9 + 1;
          }
          number_x2 = BORDER_WIDTH + rand() % ((SCREEN_WIDTH - BORDER_WIDTH) -
                                               64 - BORDER_WIDTH + 1);
          number_y2 =
              BORDER_HEIGHT + rand() % ((SCREEN_HEIGHT - BORDER_HEIGHT) - 25 -
                                        BORDER_HEIGHT + 1);
        }

        if (event.timer.source == Countdown_timer) {
          countdown_time--;
          if (countdown_time <= 0) {
            al_stop_timer(Countdown_timer);
            bIsGame = false;
            bIsEndGame = true;
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
      } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
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
      }

      if (frame > 3) {
        frame -= 3;
      }

      if (cat_frame > 3) {
        cat_frame -= 3;
      }

      char question_text[50];
      snprintf(question_text, sizeof(question_text), "%d %c ? = %d",
               current_question.operand1, current_question.operator,
               current_question.result);

      snprintf(Score_Text, sizeof(Score_Text), "Score: %d", Score);
      snprintf(Countdown_Text, sizeof(Countdown_Text), "Timer: %d",
               countdown_time);
      al_clear_to_color(al_map_rgb(100, 100, 100));
      al_draw_bitmap(Gamebackground, 0, 0, 0);
      al_draw_bitmap(question_bg, 400, 730, 0);
      al_draw_bitmap(hud, 20, 220, 0);
      if (number_active) {
        char number_text[2];
        snprintf(number_text, sizeof(number_text), "%d", random_number);
        al_draw_text(Font, al_map_rgb(255, 255, 255), number_x, number_y,
                     ALLEGRO_ALIGN_CENTER, number_text);
      }

      if (number_active2) {
        char number_text2[2];
        snprintf(number_text2, sizeof(number_text2), "%d", random_number2);
        al_draw_text(Font, al_map_rgb(255, 255, 255), number_x2, number_y2,
                     ALLEGRO_ALIGN_CENTER, number_text2);
      }
      al_draw_text(Font, al_map_rgb(0, 0, 0), 650, 800, 0, question_text);
      al_draw_text(Font, al_map_rgb(0, 0, 0), 30, 270, 0, Score_Text);
      al_draw_text(Font, al_map_rgb(0, 0, 0), 30, 300, 0, Countdown_Text);
      al_draw_bitmap_region(Sprite, 64 * (int)frame, current_frame_y, 64, 64,
                            PositionX, PositionY, 0);
      al_draw_bitmap_region(CatSprite, 64 * (int)cat_frame, cat_current_frame_y,
                            64, 64, cat_position_x, cat_position_y, 0);
      // al_play_sample(Sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
      al_flip_display();
      al_rest(0.01);
    }

    if (bIsEndGame) {

      al_clear_to_color(al_map_rgb(0, 0, 0));
      char score_text[50];
      snprintf(score_text, sizeof(score_text), "Final Score: %d", Score);
      al_draw_text(Font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                   SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, score_text);
      al_draw_text(Font, al_map_rgb(255, 255, 255), 620, 100,
                   ALLEGRO_ALIGN_CENTER, "Press ESC to close the game");
      al_draw_text(Font, al_map_rgb(255, 255, 255), 620, 150,
                   ALLEGRO_ALIGN_CENTER, "Press Enter to restart the game");

      al_flip_display();

      if (event.type = ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
          bIsMenu = true;
          bIsGame = false;
          bIsEndGame = false;
          bIsOptions = false;
          Score = 0;
          countdown_time = 45;
          al_start_timer(Countdown_timer);
        }
      }
      if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
          event.keyboard.keycode == ALLEGRO_KEY_R) {
        break;
      }
    }
  }
  al_destroy_display(Display);
  al_destroy_font(Font);
  al_destroy_event_queue(EventQueue);
  al_destroy_timer(Timer);
  al_destroy_bitmap(Sprite);
  al_destroy_bitmap(Menubackground);
  al_destroy_bitmap(question_bg);
  al_destroy_sample(Sample);

  return 0;
}