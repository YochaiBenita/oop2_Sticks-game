# pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>
#include "Resources.h"
//#include <map>

const sf::Vector2f BOARD_SIZE(600, 600);
const int NUM_OF_DATA = 5;
class Controller {
public:
	Controller();
	Controller(std::string);
	~Controller();
	void run(sf::RenderWindow&);
	void hint(const std::multimap<int, Stick*>::iterator&, const std::multimap<int, Stick*>::iterator&);
	void addToScore(int);
	void updateBlinking(Stick*);
	void resetTimer(float);
	//void debug(sf::RenderWindow&);

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


	void draw_data(sf::RenderWindow&);
	int handleClick(sf::Vector2f) const;
	void resetSFMLComponents();
	void blink();
	void saveData() const;
	//void printMessage(sf::RenderWindow& messageWind, const std::string, int offset = 0) const;

};




//std::list<Stick*>::iterator m_glowingEnd;
//std::list<Stick*>::iterator m_glowingCurr;
//void Controller::blink()
//{
//	sf::sleep(sf::seconds(0.7));
//	(*m_glowingCurr)->glow(false);
//	++m_glowingCurr;
//	if (m_glowingCurr == m_glowingEnd)
//	{
//		m_blinking = false;
//		return;
//	}
//	(*m_glowingCurr)->glow(true);
//}