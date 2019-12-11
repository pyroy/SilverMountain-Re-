#ifndef MAIN_H
#define MAIN_H

class Game {

public:
	int SCREEN_WIDTH = 0;
	int SCREEN_HEIGHT = 0;
	float H_SCALE = 3.0;
	float V_SCALE = 3.0;
	float TARGET_FPS = 60.0;
	sf::Font FONT;
	bool M_CLICK = false;
	sf::Vector2i C_POS;
	sf::Vector2f C_POS_R;
	sf::VideoMode FS;
	sf::RenderWindow& WINDOW;
	sf::Time DT;
	Game(sf::RenderWindow& w);

};

#endif