#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef GAME_CLASSES
#define GAME_CLASSES

class Wall {

	public:

		float x_pos;
		float y_pos;

		struct G_PARAMS* GAME_PARAMS;
		Sprite wall_sprite;

		Wall();

		void setup(Sprite P_SPRT, G_PARAMS* G_PRMSptr);
		void set_pos(float x_p, float y_p);

};

class Player {

	public:

		bool facing_right;

		float mov_speed;
		float x_vel;
		float y_vel;

		float x_pos;
		float y_pos;

		struct G_PARAMS* GAME_PARAMS;
		Sprite player_sprite;

		Player(Sprite P_SPRT, G_PARAMS* G_PRMSptr);

		void update(bool left_k, bool down_k, bool up_k, bool right_k);
		void collide();

		int get_x();
		int get_y();

};

#endif
