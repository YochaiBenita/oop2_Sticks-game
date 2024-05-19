#include "Stick.h"
#include <cmath>

Stick::Stick() //:m_line()
{
	int x;
	x = rand() % 3;

	m_score = COLOR_AND_SCORE[x].second;

	m_line.setOrigin(sf::Vector2f(0, WIDTH / 2));

	m_line.setFillColor(COLOR_AND_SCORE[x].first);
	m_line.setOutlineThickness(1);
	m_line.setOutlineColor(sf::Color::Black);

	x = (rand() % 5) * 10;
	m_line.setSize(sf::Vector2f(MIN_LEN + x, WIDTH));

	x = (rand() % 179) - 89;
	m_line.setRotation(x);

	int y;

	x = (rand() % (int(BOAED_SIZE.x) - 2 * BORDER)) + BORDER;
	y = (rand() % (int(BOAED_SIZE.y) - 2 * BORDER)) + BORDER;
	m_line.setPosition(sf::Vector2f(x, y));



}

void Stick::findAllIntersections(const std::list<Stick>& list,
	std::list<Stick>::iterator other)
{
	for (; other!=list.end(); ++other) //for on all obj from other to end
	{
		if (intersects(this->m_line, other->m_line))//algo from the yechezkel
		{
			m_blocking.push_back(&(*other));
			other->m_blockedBy.push_back(this);
		}
	}
	
}

bool Stick::intersects(const sf::RectangleShape&, const sf::RectangleShape&) const
{
	//algo of the seint yechezkel
	getEndPoint(other->m_line);
	return false;
}

sf::Vector2f Stick::getEndPoint(const sf::RectangleShape& obj) const
{
	float x = obj.getSize().x * std::cos(obj.getRotation());
	x += obj.getPosition().x;
	float y = obj.getSize().x * std::sin(obj.getRotation());
	y += obj.getPosition().y;
	return sf::Vector2f(x,y);
}

bool Stick::isAccessible() const
{
	return m_blockedBy.size()==0;
}

int Stick::getScore() const
{
	return m_score;
}

