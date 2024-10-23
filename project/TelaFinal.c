#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {
    // Inicializa o Allegro
    al_init();
    al_init_font_addon();
    al_install_keyboard();
    al_init_primitives_addon();

    // Cria a tela
    ALLEGRO_DISPLAY* Display = al_create_display(640, 480);
    al_set_window_position(Display, 200, 200);

    ALLEGRO_FONT* Font = al_create_builtin_font();

    // Loop principal
    bool Done = false;
    while (!Done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(al_get_default_event_queue(), &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            Done = true;
        }

        // Preenche a tela com branco
        al_clear_to_color(al_map_rgb(255, 255, 255));

        // Exibe a mensagem de fim de jogo
        al_draw_text(Font, al_map_rgb(0, 0, 0), 320, 200, ALLEGRO_ALIGN_CENTRE, "Fim de Jogo!");

        // Atualiza a tela
        al_flip_display();
    }

    // Libera recursos
    al_destroy_display(Display);
    al_destroy_font(Font);

    return 0;
}
