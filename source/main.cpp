#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_classes.h"
#include "main.h"

using namespace sf;
using namespace std;

// ------===[ Game Setup ]===------ //
VideoMode FS = VideoMode::getDesktopMode();
RenderWindow window(FS, "Silver Mountain :Re:", Style::Fullscreen);

struct G_PARAMS gpm;
struct G_PARAMS *GAME_PARAMS = &gpm;

bool left_keypress, down_keypress, up_keypress, right_keypress = false;
// -------------------------------- //

// Returns an integer specifying what actions need to be taken base on the window events.
// Has to be run to clear out events!
int get_event_action() {

	Event event;
	while (window.pollEvent(event)) {

		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) { return 1; }

	}

	return 0;

}

void setup() {

	GAME_PARAMS -> SCREEN_WIDTH = FS.width;
	GAME_PARAMS -> SCREEN_HEIGHT = FS.height;
	GAME_PARAMS -> H_SCALE = 3;
	GAME_PARAMS -> V_SCALE = 3;
	GAME_PARAMS -> TARGET_FPS = 60.0;

}

// Main game loop
int main() {

	setup();

	Player			player_obj(GAME_PARAMS);
	Wall			wall_obj(64.0, 64.0);

	Texture			player_texture;	player_texture.loadFromFile("resources/sprites/idle.png");
	Texture			wall_texture;	wall_texture.loadFromFile("resources/sprites/stone.png");

	Sprite			player_sprite(player_texture);	player_sprite.scale(GAME_PARAMS -> H_SCALE, GAME_PARAMS -> V_SCALE);
	Sprite			wall_sprite(wall_texture);		wall_sprite.scale(GAME_PARAMS -> H_SCALE, GAME_PARAMS -> V_SCALE);

	Font			consolas_font;	consolas_font.loadFromFile("resources/font/consola.ttf");
	Text			hello_text( "bruh moment", consolas_font );

	Clock			clock;
	Time			time_elapsed;

	while( window.isOpen() ) {

		time_elapsed = clock.getElapsedTime();
		wall_sprite.setPosition(wall_obj.x_pos, wall_obj.y_pos);

		if (time_elapsed.asMilliseconds() > 1000.0 / GAME_PARAMS->TARGET_FPS) {

			Time dt = clock.restart();

			// Handles all the events
			switch (get_event_action()) {
			case 1: window.close();
			}

			// Gets all the keyboard inputs, needs to move to function
			left_keypress  = Keyboard::isKeyPressed(Keyboard::Left);
			down_keypress  = Keyboard::isKeyPressed(Keyboard::Down);
			up_keypress    = Keyboard::isKeyPressed(Keyboard::Up);
			right_keypress = Keyboard::isKeyPressed(Keyboard::Right);

			// Updates player
			player_obj.update(left_keypress, down_keypress, up_keypress, right_keypress);
			player_sprite.setPosition(player_obj.x_pos, player_obj.y_pos);

			// Make all the graphics
			window.clear();
			window.draw(player_sprite);
			window.draw(wall_sprite);
			window.draw(hello_text);
			window.display();

		} else {

			;

		}

	}

	return 0;

}