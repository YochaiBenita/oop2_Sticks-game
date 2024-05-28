# pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>
#include "Resources.h"

class Controller {
public:
	Controller();
	Controller(std::string);
	void run(sf::RenderWindow&);
	void hint(const std::multimap<int, Stick*>::iterator&, const std::multimap<int, Stick*>::iterator&);
	void addToScore(int);
	void updateBlinking(Stick*);
	void resetTimer(float);
	
private:
	int m_score = 0;
	Board m_board;
	sf::Text m_data[NUM_OF_DATA];
	sf::RectangleShape m_background;
	sf::RectangleShape m_boardBackground;
	sf::RectangleShape m_buttonsGame[NUM_OF_BUTTONS_BOARD];

	sf::Clock m_clock;
	float m_timer;

	bool m_blinking = false;
	bool m_hint = false;
	std::multimap<int, Stick*>::iterator m_glowingCurr;
	std::multimap<int, Stick*>::iterator m_glowingEnd;
	Stick* m_blockedAndPressed;


	void drawData(sf::RenderWindow&);
	int handleClick(sf::Vector2f) const;
	void resetSFMLComponents();
	void handleHint();
	void saveData() const;
};

