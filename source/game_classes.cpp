#include "game_classes.h"
#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>

using namespace std;
using namespace sf;

// Player class to control player movement
Player::Player(sf::Sprite P_SPRT, Game* G_PRMSptr) {

		facing_right = true;
		mov_speed = 10.0;

		x_pos = 32.0 * G_PRMSptr->H_SCALE;
		y_pos = 32.0 * G_PRMSptr->V_SCALE;

		GAME = G_PRMSptr;
		player_sprite = P_SPRT;

		cout << "Player Class Initialized" << endl;

	}

void Player::update(bool left_k, bool down_k, bool up_k, bool right_k) {

	float bc_1[2] = { 6.0, 3.0 };
	float bc_2[2] = { 26.0, 3.0 };
	float bc_3[2] = { 6.0, 28.0 };
	float bc_4[2] = { 26.0, 28.0 };

	float old_x_pos = x_pos;

	if (right_k) { x_pos += mov_speed;  facing_right = true; }

	if (left_k) { x_pos -= mov_speed; facing_right = false; }

	if (collide(bc_1) or collide(bc_2) or collide(bc_3) or collide(bc_4)) {
		x_pos = old_x_pos;
	}

	float old_y_pos = y_pos;

	if (up_k) { y_pos -= mov_speed; }

	if (down_k) { y_pos += mov_speed; }

	if (collide(bc_1) or collide(bc_2) or collide(bc_3) or collide(bc_4)) {
		y_pos = old_y_pos;
	}

}

void Player::set_map(std::vector<std::vector<int>> map) {

	boundmap = map;
	OOB_x = boundmap.size();
	OOB_y = boundmap[0].size();

}

bool Player::collide(float c[]) {

	int corner_x = get_field_pos_x(c[0] * GAME->H_SCALE);
	int corner_y = get_field_pos_y(c[1] * GAME->V_SCALE);

	if (corner_x >= OOB_x or corner_x < 0) return false;
	if (corner_y >= OOB_y or corner_y < 0) return false;

	if (boundmap[corner_x][corner_y]) {

		return true;

	}

	return false;

}

int Player::get_field_pos_x(float offset = 0.0) {

	return (x_pos + offset) / 32 / GAME->H_SCALE;

}

int Player::get_field_pos_y(float offset = 0.0) {

	return (y_pos + offset) / 32 / GAME->V_SCALE;

}