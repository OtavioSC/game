#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
int main()
{
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display = al_create_display(600, 400);
	al_set_window_position(display,200, 200);

	ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

	ALLEGRO_BITMAP* sprite = al_load_bitmap("./Assets/sprites/knight.png");

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);

	float frame = 3.f;
	int positionX = 200, positionY = 200;
	int current_frame_y = 53;

	while (true) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_W) {
			positionY -= 3;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
			positionY += 3;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_D) {
			positionX += 3;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_A)	 {
			positionX -= 3;
		}
		frame += 0.3;
		if (frame > 8) 
		{
			frame = 3;
		}
		al_clear_to_color(al_map_rgb(100, 100, 100));
		//al_draw_bitmap(sprite, 200, 200, 100);
		al_draw_bitmap_region(sprite, 32*(int)frame, current_frame_y, 32, 53, positionX, positionY, 0);
		al_draw_text(font, al_map_rgb(0, 0, 0), 30, 30, 0, "Score: ");
		al_flip_display();
	}

	
	al_destroy_font(font);
	al_destroy_bitmap(sprite);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}