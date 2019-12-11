#include "item_container.h"
#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

Item::Item(std::string d_n = "missingname") {

	equipped = false;
	name = d_n;

}

void Item::set_marks(int index, int flag) {

	marks[index] = flag;

}

Item_DB::Item_DB() {

	Item id_0("Old Rusty Pickaxe");

	database.push_back(id_0); //item id 0, items will also need to have unique ids later on

}

void Item_DB::load_database_from_file() {

	; // Will load all the items from a database located in \resources\items\item_database.db
	  // So that we can easily edit the database with a specially programmed editor.

}

ItemContainer::ItemContainer() {

	item_vector.clear();

	add_item(Item("test item 1"));
	add_item(Item("test item 2--;;"));
	add_item(Item());

	Item p("Old Rusty Pickaxe");
	p.set_marks(1, 1);
	add_item(p);

}

int		ItemContainer::get_size()				{ return item_vector.size(); }
Item	ItemContainer::get_item(int index)		{ return item_vector[index]; }
void	ItemContainer::add_item(Item it)		{ item_vector.push_back(it); }

InventoryGraphics::InventoryGraphics(Game *gpr) {

	GAME = gpr;

	eq_rect.setSize(sf::Vector2f(4, 4));
	eqf_rect.setSize(sf::Vector2f(3, 3));

	fav_h = sf::Text(L"♥", GAME->FONT, 10);
	fav_h.setFillColor(sf::Color(255, 0, 0));

	fav_heq = sf::Text(L"♥", GAME->FONT, 8);
	fav_heq.setFillColor(sf::Color(255, 0, 0));

	inv_rect.setFillColor(sf::Color(30, 30, 30, 128));

}

void InventoryGraphics::draw_items(ItemContainer& inv) {

	for (int i = 0; i < inv.get_size(); i++) {

		Item item = inv.get_item(i);
		sf::Text d_txt(item.name, GAME->FONT, 10);
		d_txt.setPosition(10, 10 + 20 * i);

		if (GAME->M_CLICK) {

			if (GAME->C_POS.x > d_txt.getGlobalBounds().left - 2 && GAME->C_POS.x < d_txt.getGlobalBounds().left + d_txt.getGlobalBounds().width + 2) {

				if (GAME->C_POS.y > d_txt.getGlobalBounds().top - 2 && GAME->C_POS.y < d_txt.getGlobalBounds().top + d_txt.getGlobalBounds().height + 2) {

					if (item.marks[0]) { //if item is equipped

						inv.item_vector[i].set_marks(0, 0);

					}
					else {

						inv.item_vector[i].set_marks(0, 1);

					}

					GAME->M_CLICK = false;

				}

			}

		}

		GAME->WINDOW.draw(d_txt);

		if (item.marks[0] && !item.marks[1]) { //if equipped

			eq_rect.setPosition(3, 16 + 20 * i);
			GAME->WINDOW.draw(eq_rect);

		}
		else if (item.marks[1] && !item.marks[0]) { //if faved

			fav_h.setPosition(3, 10 + 20 * i);
			GAME->WINDOW.draw(fav_h);

		}
		else if (item.marks[0] && item.marks[1]) { //if equipped AND faved

			
			eqf_rect.setPosition(3, 13 + 20 * i);
			GAME->WINDOW.draw(eqf_rect);

			fav_heq.setPosition(3, 16 + 20 * i);
			GAME->WINDOW.draw(fav_heq);

		}

	}

}

void InventoryGraphics::draw_inv_rect() {

	inv_rect.setSize(sf::Vector2f(inv_reach, GAME->SCREEN_HEIGHT));
	GAME->WINDOW.draw(inv_rect);

}

void InventoryGraphics::update_and_draw(ItemContainer& inv) {

	if (inv_is_open && !inv_anim_done) {
		inv_anim_frames = std::fmin(10.0, inv_anim_frames + GAME->DT.asMilliseconds() / 7);
		inv_reach = inv_anim_frames * 25;
		if (inv_anim_frames == 10) {
			inv_anim_done = true;
		}
	}
	else if (!inv_is_open && !inv_anim_done) {
		inv_anim_frames = std::fmin(10.0, inv_anim_frames + GAME->DT.asMilliseconds() / 7);
		inv_reach = 250 - inv_anim_frames * 25;
		if (inv_anim_frames == 10) {
			inv_anim_done = true;
		}
	}

	if (inv_is_open || !inv_anim_done) draw_inv_rect();
	if (inv_is_open && inv_anim_done) draw_items(inv);

}

void InventoryGraphics::update_keypress(bool kp) {

	if (kp && inv_anim_done && receiving_kp) {
		inv_is_open = !inv_is_open;
		inv_anim_done = false;
		inv_anim_frames = 0;
		receiving_kp = false;
	}
	if (!receiving_kp && !kp) receiving_kp = true;

}