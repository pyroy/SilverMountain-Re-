#include <SFML/Graphics.hpp>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Tile {

public:
	sf::Vector2i position;
	int tile_type;
	int max_minetime = 120;
	int minetime = 0;

	Tile(sf::Vector2i p, int t);
	bool is_empty();

};

class Maploader {

	public:

		sf::RenderTexture map;
		std::vector< std::vector<int> > bound_map;
		std::vector< std::vector<Tile> > tile_map;

		sf::RectangleShape empty;
		sf::RenderStates blend_mode_empty;

		int OOB_x;
		int OOB_y;

		float tile_size = 32.0;

		class Game* GAME;

		Maploader(std::string f, Game* g);
		Tile* get_tile_at(sf::Vector2f);
		void remove_tile_at(sf::Vector2i);

};

#endif