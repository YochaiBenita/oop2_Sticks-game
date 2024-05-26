# pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>

const sf::Vector2f BOARD_SIZE(600, 600);

class Controller {
public:
	Controller();
	Controller(std::string);
	~Controller();
	void run(sf::RenderWindow&);
	void glow(std::list<Stick*>::iterator, std::list<Stick*>::iterator);
	//void debug(sf::RenderWindow&);

private:
	int m_score = 0;
	Board m_board;
	sf::RectangleShape m_backgraund;
	sf::Clock m_clock;
	float m_timer = 120;

	bool m_blinking = false;
	std::list<Stick*>::iterator m_glowingEnd;
	std::list<Stick*>::iterator m_glowingCurr;

};