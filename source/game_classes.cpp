#include "game_classes.h";
#include "main.h";
#include <iostream>

using namespace std;

Wall::Wall(float x_p = 0.0, float y_p = 0.0) {

	cout << "Wall Class Initialized" << endl;

	x_pos = x_p;
	y_pos = y_p;

};

// Player class to control player movement
Player::Player(struct G_PARAMS* G_PRMSptr) {

		facing_right = true;
		mov_speed = 10.0;

		x_vel = 0.0;
		y_vel = 0.0;

		x_pos = 0.0;
		y_pos = 0.0;

		GAME_PARAMS = G_PRMSptr;

		cout << "Player Class Initialized" << endl;

	}

void Player::update(bool left_k, bool down_k, bool up_k, bool right_k) {

		x_vel = 0.0;
		y_vel = 0.0;

		if (right_k) { x_vel = mov_speed; facing_right = true; }

		if (left_k) { x_vel = -mov_speed; facing_right = false; }

		if (up_k) { y_vel = -mov_speed; }

		if (down_k) { y_vel = mov_speed; }

		x_pos += x_vel;
		y_pos += y_vel;

		collide();

}

void Player::collide() {

	if (x_pos + 32.0 * GAME_PARAMS->H_SCALE > GAME_PARAMS->SCREEN_WIDTH) {
		x_pos = (float)GAME_PARAMS->SCREEN_WIDTH - 32.0 * GAME_PARAMS->H_SCALE;
	}

	if (x_pos < 0) {
		x_pos = 0;
	}

	if (y_pos + 32.0 * GAME_PARAMS->V_SCALE > GAME_PARAMS->SCREEN_HEIGHT) {
		y_pos = (float)GAME_PARAMS->SCREEN_HEIGHT - 32.0 * GAME_PARAMS->V_SCALE;
	}

	if (y_pos < 0) {
		y_pos = 0;
	}

}

int Player::get_x() {
	return x_pos;
}

int Player::get_y() {
	return y_pos;
}