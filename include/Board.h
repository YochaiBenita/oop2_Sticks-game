# pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include "Stick.h"
#include <string>

class Board
{
public:
	Board();
	Board(std::string);
	bool intersect();
	void play(sf::RenderWindow&);
	bool to_exit();
	void draw(sf::RenderWindow&)const;

private:
	std::list<Stick> m_sticksList;
	std::multimap<int, Stick*> m_accessible;

};