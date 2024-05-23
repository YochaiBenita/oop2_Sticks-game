# pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include "Stick.h"
#include <string>

class Controller;

class Board
{
public:
	Board(Controller*);
	Board(Controller* , const std::string);
	~Board();
	bool intersect();
	void play(sf::RenderWindow&, const sf::Vector2f&);
	//bool to_exit();
	void draw(sf::RenderWindow&)const;
	bool finished()const;
	static void addToAccessible(Stick*);
	void debug(sf::RenderWindow&);

private:
	std::list<Stick> m_sticksList;
	static std::multimap<int, Stick*> m_accessible;

	Controller* m_controller;

	void removeAccessible(Stick*);
};