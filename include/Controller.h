# pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

const sf::Vector2f BOARD_SIZE(600, 600);

class Controller {
public:
	Controller(Board*);
	~Controller();
	void run(sf::RenderWindow&);

private:
	//int m_score;
	Board* m_board;
	sf::RectangleShape m_backgraund;

};