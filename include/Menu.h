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
	sf::RectangleShape m_button[NUM_OF_BUTTONS_MENU];
	sf::RectangleShape m_background;
	sf::RenderWindow m_wind;
	Controller* m_controller;


	int handle_click(sf::Vector2f) const;
	void draw_buttons(sf::RenderWindow&) const;
};