#include "maploader.h"
#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

Tile::Tile(sf::Vector2i pos, int type) {

	position = pos;
	tile_type = type;

}

bool Tile::is_empty() {

	return position == sf::Vector2i(-1, -1) && tile_type == 0;

}

Maploader::Maploader(std::string f_path, Game* G_PRMSptr) {

	GAME = G_PRMSptr;

	empty.setSize(sf::Vector2f(tile_size * GAME->H_SCALE, tile_size * GAME->V_SCALE));
	empty.setFillColor(sf::Color::Transparent);

	blend_mode_empty = sf::RenderStates(sf::BlendMode(sf::BlendMode::Zero, sf::BlendMode::One, sf::BlendMode::Add, sf::BlendMode::One, sf::BlendMode::Zero, sf::BlendMode::Add));

	ifstream map_file;
	map_file.open("resources/maps/"+f_path+".txt");

	int map_w = 7;
	int map_h = 7;
	int ind = 0;
	int collide = 0;
	int texture_amount = 1;
	int void_index = -1;
	char txt_path[20];

	std::map<int, sf::Sprite> sprt_lookup;
	std::map<int, sf::Texture> text_lookup;
	std::map<int, bool> bound_lookup;

	if (map_file.is_open()) {

		string line;

		//first line dictates map size
		getline(map_file, line);
		sscanf_s(line.c_str(), "%ix%i:%i", &map_w, &map_h, &texture_amount);
		map.create(map_w * tile_size * GAME->H_SCALE, map_h * tile_size * GAME->V_SCALE);

		//discard empty line
		getline(map_file, line);

		//load all textures
		for (int i = 0; i < texture_amount; i++) {

			getline(map_file, line);

			sscanf_s(line.c_str(), "%i:%i:%s", &ind, &collide, txt_path, 20);

			if( (string)txt_path != (string)"void" ) {

				sf::Texture txt;
				txt.loadFromFile("resources/sprites/" + (string)txt_path + ".png");

				//store textures, or else the sprite will blank out.
				text_lookup[ind] = txt;

				sf::Sprite tmp_sprite(text_lookup[ind]);
				tmp_sprite.scale(GAME->H_SCALE, GAME->V_SCALE);

				sprt_lookup[ind] = tmp_sprite;
				bound_lookup[ind] = (bool)collide;

			} else void_index = ind;

		}

		//discard next line
		getline(map_file, line);

		//go over the map data and get the sprites from the sprite lookup
		int tile_index_x = 0;
		int tile_index_y = 0;

		for (int i = 0; i < map_h; i++) {

			getline(map_file, line);

			std::vector<int> this_row; //for boundmap
			std::vector<Tile> this_row_tm; //for tilemap to look up tiles

			for (int c = 0; c < line.size(); c++) {

				if (line[c] != ';') {

					int lookup_ind = line[c] - '0';

					if (lookup_ind != void_index) {

						sprt_lookup[lookup_ind].setPosition(tile_size * tile_index_x * GAME->H_SCALE, tile_size * tile_index_y * GAME->V_SCALE);
						map.draw(sprt_lookup[lookup_ind]);

					}

					this_row_tm.push_back(Tile(sf::Vector2i(tile_index_x, tile_index_y), lookup_ind));
					this_row.push_back(bound_lookup[lookup_ind]);

					tile_index_x++;

				}

			}

			tile_map.push_back(this_row_tm);
			bound_map.push_back(this_row);
			this_row.clear();

			tile_index_y++;
			tile_index_x = 0;

		}

		map.display();

		OOB_x = bound_map.size();
		OOB_y = bound_map[0].size();

		map_file.close();

	} else cout << "Unable to open map file." << endl;

}

Tile *Maploader::get_tile_at(sf::Vector2f pos_f) {

	if (pos_f.x < 0) return &Tile(sf::Vector2i(-1, -1), 0);
	if (pos_f.y < 0) return &Tile(sf::Vector2i(-1, -1), 0);

	int lookup_x = pos_f.x / tile_size / GAME->H_SCALE;
	int lookup_y = pos_f.y / tile_size / GAME->V_SCALE;

	if (lookup_x >= OOB_x) return &Tile(sf::Vector2i(-1, -1), 0);
	if (lookup_y >= OOB_y) return &Tile(sf::Vector2i(-1, -1), 0);;
	
	return &tile_map[lookup_y][lookup_x];

}

void Maploader::remove_tile_at(sf::Vector2i pos) {

	if (pos != sf::Vector2i(-1, -1)) {

		tile_map[pos.y][pos.x] = Tile(sf::Vector2i(pos.x, pos.y), 0);
		bound_map[pos.x][pos.y] = 0;
		empty.setPosition(tile_size * pos.x * GAME->H_SCALE, tile_size * pos.y * GAME->H_SCALE);
		map.draw(empty, blend_mode_empty);

	}

}