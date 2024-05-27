#include "Board.h"
#include <iostream>
#include <fstream>
#include "Controller.h"
#include "InvalidFileException.h"
#include "InvalidContentFileException.h"

std::multimap<int, Stick* , std::greater<int>> Board::m_accessible;

Board::Board(Controller* con) : m_controller(con), m_collected(0)
{
	int x = rand() % 30 + 20;//num of sticks betwean 20-49
	for (int i = 0; i < x; i++) 
	{
		m_sticksList.push_front(Stick());
	}

	auto stick = m_sticksList.begin();

	for (int i = 0; i < x; i++)
	{
		stick->findAllIntersections(m_sticksList ,++stick);
	}

	stick = m_sticksList.begin();

	while (stick != m_sticksList.end())
	{
		stick = std::find_if(stick, m_sticksList.end(), [](auto stick) {return stick.isAccessible(); });
		if (stick != m_sticksList.end())
		{
			m_accessible.insert({ stick->getScore(), &(*stick) });
			stick++;
		}
	}
}

Board::Board(Controller* con, const std::string fileName) : m_controller(con), m_collected(0) //����� ��� �� ����� �����.
{
	auto file = std::ifstream(fileName);
	if (!file.is_open())
	{
		throw InvalidFileException();
	}
	//using iss for reading the data

}

Board::~Board()
{
	m_accessible.clear();
}

void Board::play(sf::RenderWindow& m_wind, const sf::Vector2f& mousePosition)
{
	auto stick = std::find_if(m_sticksList.begin(), m_sticksList.end(), [mousePosition](auto stick) {return stick.isPressed(mousePosition); });
	if (stick != m_sticksList.end()) 
	{
		if (stick->handleClick())
		{
			removeAccessible(&(*stick));
			m_sticksList.remove(*stick);
			m_collected++;
		}
		else
		{
			m_controller->updateBlinking(&(*stick));
			m_controller->addToScore(-5);
		}
	}
}

void Board::draw(sf::RenderWindow& m_wind) const
{
	std::for_each(m_sticksList.rbegin(), m_sticksList.rend(), [&m_wind](auto stick) {m_wind.draw(stick.getRect()); });

}

bool Board::finished() const
{
	return m_sticksList.empty();
}

void Board::addToAccessible(Stick* stick)
{
	m_accessible.insert({stick->getScore(), stick});
}

int Board::getCollectedSticks() const
{
	return m_collected;;
}

int Board::getRemainedSticks() const
{
	return m_sticksList.size();
}

int Board::getAccessibleStics() const
{
	return m_accessible.size();
}

std::multimap<int, Stick*>::iterator Board::getAccessibleBegin() const
{
	return m_accessible.begin();
}

std::multimap<int, Stick*>::iterator Board::getAccessibleEnd() const
{
	return m_accessible.end();
}


//void Board::debug(sf::RenderWindow& m_wind)
//{
//	for (auto it = m_accessible.begin(); it != m_accessible.end(); it++)
//	{
//		Stick& s = *(it->second);
//		s.glow(true);
//		m_wind.draw(s.getRect());
//	}
//}


void Board::removeAccessible(Stick* stick)
{
	auto it = std::find_if(m_accessible.begin(), m_accessible.end(),
		[stick](const auto pair) {return pair.second == stick; });
	if (it != m_accessible.end())
	{
		m_controller->addToScore(it->first);
		it = m_accessible.erase(it);
	}



	//auto range = m_accessible.equal_range(stick->getScore());
	//for (auto it = range.first; it != range.second; ++it)
	//{
	//	if (it->second == &(*stick))
	//	{
	//		std::cout << "erase access start " << m_accessible.size() << '\n';
	//		m_accessible.erase(it);
	//		std::cout << "erase access end " << m_accessible.size() << '\n';
	//		break;
	//	}
	//}
}


