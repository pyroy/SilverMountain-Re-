#include <SFML/Graphics.hpp>
#include "item_container.h"
#include "main.h"
using namespace sf;

#ifndef GAME_CLASSES
#define GAME_CLASSES

class Player {

	public:

		bool facing_right;

		float mov_speed;

		float x_pos;
		float y_pos;

		ItemContainer inventory;

		Game* GAME;
		Sprite player_sprite;

		std::vector<std::vector<int>> boundmap;
		int OOB_x;
		int OOB_y;

		Player(sf::Sprite s, Game *g);

		void set_map(std::vector<std::vector<int>>);
		void update(bool, bool, bool, bool);
		bool collide(float[]);
		int get_field_pos_x(float);
		int get_field_pos_y(float);

};

#endif
