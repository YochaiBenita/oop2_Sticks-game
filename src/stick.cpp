#include "Stick.h"
#include <cmath>
#include <algorithm> 
#include "Controller.h"
#include <iostream>
#include <sstream>
#include "Board.h"
#include "InvalidContentFileException.h"

Stick::Stick()
{
	int x;
	x = rand() % 3;

	m_score = COLOR_AND_SCORE[x].second;

	m_line.setOrigin(sf::Vector2f(0, WIDTH / 2));

	m_line.setFillColor(COLOR_AND_SCORE[x].first);
	m_line.setOutlineThickness(3);
	m_line.setOutlineColor(sf::Color::Black);

	x = (rand() % 5) * 10;
	m_line.setSize(sf::Vector2f(MIN_LEN + x, WIDTH));

	x = (rand() % 179) - 89;
	m_line.setRotation(x);

	int y;

	x = (rand() % (int(BOARD_SIZE.x) - 2 * BORDER)) + 300 +BORDER;
	y = (rand() % (int(BOARD_SIZE.y) - 2 * BORDER)) + BORDER;
	m_line.setPosition(sf::Vector2f(x, y));

}

Stick::Stick(std::string line)
{
	std::istringstream iss(line);
	int score, len, rotation, position_x, position_y;
	iss >> score >> len >> rotation >> position_x >> position_y;
	std::cout << "s\n";
	if (!((score == 10 || score == 15 || score == 20) &&
		(len >= MIN_LEN && len <= MIN_LEN + 50) &&
		((rotation % 90 != 0) || (rotation % 180 == 0)) &&
		(position_x - BORDER - 300 >= 0 && position_x + BORDER - 300 <= 900) &&
		(position_y - BORDER >= 0 && position_y + BORDER <= 600)))
	{
		throw InvalidContentFileException();
	}
	std::cout << "f\n";


	m_score = score;

	for (int i = 0; i < NUM_OF_COLORS; i++) {
		if (COLOR_AND_SCORE[i].second == score) {
			m_line.setFillColor(COLOR_AND_SCORE[i].first);
		}
	}

	m_line.setOrigin(sf::Vector2f(0, WIDTH / 2));
	m_line.setSize(sf::Vector2f(len, WIDTH));
	m_line.setRotation(rotation);
	m_line.setPosition(sf::Vector2f(position_x, position_y));
	m_line.setOutlineThickness(3);
	m_line.setOutlineColor(sf::Color::Black);
	
}

void Stick::findAllIntersections(const std::list<Stick>& list,
	std::list<Stick>::iterator obj)
{
	sf::Vector2f endPointLine = getEndPoint(m_line);//test

	//auto obj = std::find(list.begin(), list.end(), this);
	//obj++;

	for (; obj != list.end(); ++obj) //for on all obj from other to end
	{
		sf::Vector2f endPointOther = getEndPoint(obj->getRect());//test

		if (intersected(m_line.getPosition(), endPointLine, obj->getRect().getPosition(), endPointOther))//algo from the yechezkel
		{
			m_blocking.push_back(&(*obj));
			obj->m_blockedBy.push_back(this);
		}
	}
}

bool Stick::isAccessible() const
{
	return m_blockedBy.empty();
}

int Stick::getScore() const
{
	return m_score;
}

sf::RectangleShape Stick::getRect() const
{
	return m_line;
}

bool Stick::isPressed(const sf::Vector2f mousePosition) const
{
	const auto transformedPoint = m_line.getTransform().getInverse().transformPoint(mousePosition);
	return m_line.getLocalBounds().contains(transformedPoint);
}

bool Stick::handleClick()
{
	if (m_blockedBy.empty())
	{
		std::for_each(m_blocking.begin(), m_blocking.end(), [this](auto blocked) {blocked->removeBlockedBy(this); });
		return true;
	}
	else
	{
		glowBlockingSticks(true);
		return false;
	}
}

void Stick::removeBlockedBy(Stick* stick)
{
	m_blockedBy.remove(stick);
	if (m_blockedBy.empty())
	{
		Board::addToAccessible(this);
	}
}

void Stick::glow(bool val)
{
	m_line.setOutlineColor((val) ? sf::Color::Green : sf::Color::Black);
}

void Stick::glowBlockingSticks(bool val)
{
	std::for_each(m_blockedBy.begin(), m_blockedBy.end(), [val](auto stick) {stick->glow(val); });
}

std::list<Stick*>::iterator Stick::getBlockedByBegin()
{
	return m_blockedBy.begin();
}

std::list<Stick*>::iterator Stick::getBlockedByEnd()
{
	return m_blockedBy.end();
}


//-----------------------------
bool Stick::intersected(const sf::Vector2f& p1, const sf::Vector2f& q1, const sf::Vector2f& p2, const sf::Vector2f& q2) const
{
	// Find the four orientations needed for general and 
	   // special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}



//bool Stick::intersects(const sf::RectangleShape& line, const sf::RectangleShape& other) const
//{
//	//algo of the seint yechezkel
//	/*sf::Vector2f endPointLine = getEndPoint(line);
//	sf::Vector2f endPointOther = getEndPoint(other);*/
//
//	return false;
//}

sf::Vector2f Stick::getEndPoint(const sf::RectangleShape& obj) const
{
	float x = obj.getOrigin().x + obj.getSize().x * std::cos(PI * obj.getRotation() / 180);
	x += obj.getPosition().x;
	float y = obj.getOrigin().y + obj.getSize().x * std::sin(PI * obj.getRotation() / 180);
	y += obj.getPosition().y;
	return sf::Vector2f(x,y);
}

//bool Stick::intersects(const sf::Vector2f&, const RectangleShape, const sf::Vector2f&, const sf::Vector2f&) const
//{
//	return false;
//}

int Stick::orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) const
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

bool Stick::onSegment(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) const
{
	return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

bool operator==(const Stick& first, const Stick& second)
{
	return (&first)==(&second);
}

std::ostream& operator << (std::ostream& os, const Stick& obj)
{
	auto rect = obj.getRect();
	
	os << obj.getScore() << ' '
		<< rect.getSize().x << ' '
		<< rect.getRotation() << ' '
		<< rect.getPosition().x << ' ' 
		<< rect.getPosition().y;

	return os;
}