#include <SFML/Graphics.hpp>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Maploader {

	public:

		std::vector<sf::Texture> texture_container;

		struct G_PARAMS* GAME_PARAMS;

		Maploader(std::string filepath, struct G_PARAMS* G_PRMSptr);

		int get_sprite_count();
		sf::Sprite get_sprite_at_index(int index);

};

#endif