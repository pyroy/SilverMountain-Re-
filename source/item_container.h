#include <SFML/Graphics.hpp>
#include <vector>

#ifndef IC_H
#define IC_H

class Item {

public:
	std::string name;
	bool equipped;
	int marks[2] = { 0, 0 };
	int equipment_slot = 0;
	std::string unique_identifier = "no implementation as of yet";

	// 0 is unassigned slot, will not be able to equip
	// 1 is helmet
	// 2 is body armor
	// 3 is weapon/shield LH
	// 4 is weapon/shield RH
	// 5 is greaves
	// 6 is boots
	// 7 is pauldrons
	// 8 is gloves
	// 9 & 10 are rings
	// 11 is amulet
	// 12 is free slot (debug only)

	Item(std::string);
	void set_marks(int, int); //temporary way of marking items. set_marks(index of marks, value)

};

class Item_DB {

public:
	std::vector<Item> database;

	Item_DB();
	void load_database_from_file();

};

class ItemContainer {

public:

	std::vector< Item > item_vector;

	ItemContainer();

	int get_size();
	Item get_item(int);
	void add_item(Item);

};

class InventoryGraphics {

public:

	sf::RectangleShape eq_rect;
	sf::RectangleShape eqf_rect;
	sf::RectangleShape inv_rect;

	sf::Text fav_h;
	sf::Text fav_heq;

	class Game *GAME;

	float inv_anim_frames = 0.0;
	int inv_reach = 0;
	bool inv_is_open = false;
	bool inv_anim_done = true;
	bool receiving_kp = true;

	InventoryGraphics(Game*);

	void draw_items(ItemContainer&);
	void draw_inv_rect();
	void update_and_draw(ItemContainer&);
	void update_keypress(bool);

};

#endif