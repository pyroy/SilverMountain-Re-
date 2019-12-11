#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_classes.h"
#include "maploader.h"
#include "main.h"

using namespace sf;
using namespace std;

// ------===[ Game Setup ]===------ //

bool left_keypress = false, down_keypress = false, up_keypress = false, right_keypress = false;

Game::Game(sf::RenderWindow& w)
	: WINDOW(w)
{
	SCREEN_HEIGHT = w.getSize().y;
	SCREEN_WIDTH = w.getSize().x;
	H_SCALE = 3.0;
	V_SCALE = 3.0;
}

sf::VideoMode FS(1280, 720);
RenderWindow window(FS, "Silver Mountain :Re:");

class Game GAME_OBJ(window);
class Game* GAME = &GAME_OBJ;

void setup() {

	GAME->FS = FS;
	GAME->SCREEN_WIDTH = GAME->FS.width;
	GAME->SCREEN_HEIGHT = GAME->FS.height;
	GAME->H_SCALE = 3;
	GAME->V_SCALE = 3;
	GAME->TARGET_FPS = 60.0;
	GAME->FONT.loadFromFile("resources/font/consola.ttf");

}

// -------------------------------- //

// Main game loop
int main() {

	setup();

	Texture			player_texture;	player_texture.loadFromFile("resources/sprites/idle.png");
	Texture			wall_texture;	wall_texture.loadFromFile("resources/sprites/stone.png");

	Sprite			player_sprite(player_texture);	player_sprite.scale(GAME -> H_SCALE, GAME -> V_SCALE);
	Sprite			wall_sprite(wall_texture);		wall_sprite.scale(GAME -> H_SCALE, GAME -> V_SCALE);

	Text			hello_text( "^click pos", GAME->FONT );

	Player			player_obj(player_sprite, GAME);

	Maploader       map1_g("test_map/groundmap", GAME);
	Maploader       map1_z("test_map/zetamap", GAME);

	Clock			clock;
	Time			time_elapsed;

	Tile*			empty = &Tile(sf::Vector2i(-1, -1), 0);
	Tile*			mining_focus = empty;
	vector<Tile*>   mining_bar_list;

	InventoryGraphics Inv_G(GAME);

	while(GAME->WINDOW.isOpen() ) {

		player_obj.set_map(map1_z.bound_map);
		time_elapsed = clock.getElapsedTime();

		if (time_elapsed.asMilliseconds() > 1000.0 / GAME->TARGET_FPS) {

			Time dt = clock.restart();
			GAME->DT = dt;

			// Handles all the events
			Event event;
			while (GAME->WINDOW.pollEvent(event)) {

				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) GAME->WINDOW.close();

				if (event.type == Event::MouseButtonPressed) {

					GAME -> M_CLICK = true;
					GAME -> C_POS = Mouse::getPosition(GAME->WINDOW);

				} 

			}

			// Gets all the keyboard inputs, needs to move to function
			left_keypress  = Keyboard::isKeyPressed(Keyboard::A);
			down_keypress  = Keyboard::isKeyPressed(Keyboard::S);
			up_keypress    = Keyboard::isKeyPressed(Keyboard::W);
			right_keypress = Keyboard::isKeyPressed(Keyboard::D);

			// Updates player
			player_obj.update(left_keypress, down_keypress, up_keypress, right_keypress);
			player_obj.player_sprite.setPosition(player_obj.x_pos, player_obj.y_pos);

			sf::View field_view = GAME->WINDOW.getDefaultView();
			field_view.setCenter(player_obj.x_pos + 16.0 * GAME->H_SCALE, player_obj.y_pos + 16.0 * GAME->V_SCALE);

			if (GAME->M_CLICK) GAME->C_POS_R = sf::Vector2f(GAME->C_POS.x + player_obj.x_pos - 591, GAME->C_POS.y + player_obj.y_pos - 311);

			//---===[Make all the field graphics]===---
			GAME->WINDOW.clear();

			GAME->WINDOW.setView(field_view);

			GAME->WINDOW.draw( sf::Sprite( map1_g.map.getTexture() ) );
			GAME->WINDOW.draw(player_obj.player_sprite);
			GAME->WINDOW.draw( sf::Sprite( map1_z.map.getTexture() ) );
			hello_text.setPosition(GAME->C_POS_R.x - 8, GAME->C_POS_R.y - 10);
			GAME->WINDOW.draw(hello_text);

			for (int i = 0; i < mining_bar_list.size(); i++) {

				int health = mining_bar_list[i]->max_minetime - mining_bar_list[i]->minetime;
				if (health == 0) {

					mining_bar_list.erase(mining_bar_list.begin() + i);
					i -= 1;
					continue;

				}
				float health_ratio = (float)health / (float)mining_bar_list[i]->max_minetime;

				float life_pixels = 75 * health_ratio;

				sf::RectangleShape greenbar;
				sf::RectangleShape redbar;

				greenbar.setSize(sf::Vector2f(life_pixels, 4));
				redbar.setSize(sf::Vector2f(75 - life_pixels, 4));

				greenbar.setFillColor(sf::Color(0, 255, 0));
				redbar.setFillColor(sf::Color(255, 0, 0));

				greenbar.setPosition((mining_bar_list[i]->position.x * 32.0 + 16) * GAME->H_SCALE - 75/2, (mining_bar_list[i]->position.y * 32.0 + 32) * GAME->V_SCALE);
				redbar.setPosition((mining_bar_list[i]->position.x * 32.0 + 16) * GAME->H_SCALE - 75/2 + life_pixels, (mining_bar_list[i]->position.y * 32.0 + 32) * GAME->V_SCALE);

				GAME->WINDOW.draw(greenbar);
				GAME->WINDOW.draw(redbar);

			}

			//---===[Make Inventory Graphics]===---

			GAME->WINDOW.setView( GAME->WINDOW.getDefaultView() );

			Inv_G.update_keypress( Keyboard::isKeyPressed( Keyboard::I ) );
			Inv_G.update_and_draw( player_obj.inventory );

			//-----------------------------------

			if (GAME->M_CLICK) {

				mining_focus = map1_z.get_tile_at(GAME->C_POS_R);
				if (mining_focus->tile_type == 0) { mining_focus = empty; }

				if (!mining_focus->is_empty() && mining_focus->minetime == 0) {

					mining_bar_list.push_back(mining_focus);

				}

			}

			if (!mining_focus->is_empty()) {

				if (mining_focus->minetime < mining_focus->max_minetime) {

					mining_focus->minetime += 1;

				}
				else {

					map1_z.remove_tile_at(mining_focus->position);
					mining_focus = empty;

				}

			}

			GAME->WINDOW.display();
			GAME->M_CLICK = false;

		}

	}

	return 0;

}