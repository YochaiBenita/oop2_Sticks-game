# pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <ostream>

class Stick
{
public:
	Stick();
	Stick(std::string);
	void findAllIntersections(const std::list<Stick>&, std::list<Stick>::iterator);
	bool isAccessible() const;
	int getScore() const;
	sf::RectangleShape getRect()const;
	bool isPressed(const sf::Vector2f)const;
	bool handleClick();
	void glow(bool);
	void glowBlockingSticks(bool);

private:
	std::list<Stick*> m_blocking;
	std::list<Stick*> m_blockedBy;
	sf::RectangleShape m_line;
	int m_score;
	
	void removeBlockedBy(Stick*);
	std::list<Stick*>::iterator getBlockedByBegin();
	std::list<Stick*>::iterator getBlockedByEnd();
	bool intersected(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;
	sf::Vector2f getEndPoint(const sf::RectangleShape&) const;
	int orientation(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;
	bool onSegment(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;

};

bool operator == (const Stick&, const Stick&);
std::ostream& operator << (std::ostream&, const Stick&);
