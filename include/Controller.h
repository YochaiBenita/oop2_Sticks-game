# pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
class Controller {
public:
	Controller(Board*);
	~Controller();
	void run(sf::RenderWindow&);

private:
	//int m_score;
	Board* m_board;
	bool m_toExit = false;
};