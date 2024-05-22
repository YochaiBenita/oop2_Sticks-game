#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Controller.h"


class Menu {
public:
	Menu();
	void show_menu();
	void show_help();

private:
	sf::Sprite m_button[NUM_OF_BUTTONS];
	sf::Sprite m_background;
	sf::RenderWindow m_wind;
	Controller* m_controller;


	int handle_click(sf::Vector2f) const;
	void draw_buttons(sf::RenderWindow&) const;
};