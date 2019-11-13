#include "maploader.h";
#include <SFML/Graphics.hpp>
#include "main.h";
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Maploader::Maploader(string filepath, G_PARAMS* G_PRMSptr) {

	GAME_PARAMS = G_PRMSptr;

	ifstream map_file;
	map_file.open("resources/maps/"+filepath+"/groundmap.txt");

	if (map_file.is_open()) {

		string line;

		while (getline(map_file, line)) {

			cout << line << endl;

			sf::Texture txt;
			txt.loadFromFile("resources/sprites/tile_dirt.png");

			texture_container.push_back( txt );

		}

		map_file.close();

	} else cout << "Unable to open map file." << endl;

}

int Maploader::get_sprite_count() {

	return texture_container.size();

}

sf::Sprite Maploader::get_sprite_at_index(int index) {

	sf::Sprite tmp_sprite( texture_container[index] );
	tmp_sprite.scale(GAME_PARAMS->H_SCALE, GAME_PARAMS->V_SCALE);
	tmp_sprite.setPosition( 32.0 * index * GAME_PARAMS->H_SCALE, 32.0 * index * GAME_PARAMS->V_SCALE);
	return tmp_sprite;

}