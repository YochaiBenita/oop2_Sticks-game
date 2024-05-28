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
	Board();
	Board(Controller* , const std::string);
	~Board();
	void play(Controller*, const sf::Vector2f&);
	void draw(sf::RenderWindow&)const;
	bool finished()const;
	static void addToAccessible(Stick*);
	int getCollectedSticks() const;
	int getRemainedSticks() const;
	int getAccessibleStics() const;
	void writeSticks(std::ofstream&) const;

	std::multimap<int, Stick*>::iterator getAccessibleBegin() const;
	std::multimap<int, Stick*>::iterator getAccessibleEnd() const;



private:
	std::list<Stick> m_sticksList;
	static std::multimap<int, Stick* ,std::greater<int> > m_accessible;
	int m_collected = 0;

	void findAllIntersections();
	int removeAccessible(Stick*);
};