# pragma once
#include <SFML/Graphics.hpp>
#include <list>

const int WIDTH = 20;
const int MIN_LEN = 150;
const int BORDER = 20;
const long double PI = 3.14159265358979323846;

const std::pair <sf::Color, int> COLOR_AND_SCORE[] = {
	{sf::Color::Red, 100},
	{sf::Color::Cyan, 150},
	{sf::Color::Blue, 180}
}; //holding color and score

class Stick
{
public:
	Stick();
	//void findAllIntersections(const std::list<Stick*>& list);
	void findAllIntersections(const std::list<Stick>&, std::list<Stick>::iterator);
	bool isAccessible() const;
	int getScore() const;
	sf::RectangleShape getRect()const;
	bool isPressed(const sf::Vector2f)const;
	bool handleClick();
	void removeBlockedBy(Stick*);
	void glow(bool);
	//std::list<Stick*> getBlockedByList()const;
	std::list<Stick*>::iterator getBlockedByBegin();
	std::list<Stick*>::iterator getBlockedByEnd();

	bool intersected(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;
	//bool intersects(const sf::Vector2f&, const RectangleShape, const sf::Vector2f&, const sf::Vector2f&) const;
	sf::Vector2f getEndPoint(const sf::RectangleShape&) const;
	int orientation(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;
	bool onSegment(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&) const;
	
	//void blockedBy(std::list<Stick>::iterator);

private:
	std::list<Stick*> m_blocking;
	std::list<Stick*> m_blockedBy;
	
	sf::RectangleShape m_line;
	int m_score;
	sf::Vector2f m_startPoint;
};

bool operator == (const Stick&, const Stick&);