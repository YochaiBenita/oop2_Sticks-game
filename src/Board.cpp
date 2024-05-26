#include "Board.h"
#include <iostream>
#include <fstream>
#include "Controller.h"
#include "InvalidFileException.h"
#include "InvalidContentFileException.h"

std::multimap<int, Stick*> Board::m_accessible;

Board::Board(Controller* con) : m_controller(con)
{
	int x = rand() % 30 + 20;//num of sticks betwean 20-49
	for (int i = 0; i < x; i++) 
	{
		m_sticksList.push_front(Stick());
	}

	//for (auto stick : m_sticksList)
	//{
	//	stick.findAllIntersections(m_sticksList);
	//}

	auto stick = m_sticksList.begin();

	//std::for_each(stick, m_sticksList.end(), [](auto stick) {stick.findAllIntersections(); });

	for (int i = 0; i < x; i++)
	{
		stick->findAllIntersections(m_sticksList ,++stick);
	}

	//checking all intersections
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

Board::Board(Controller* con, const std::string fileName) : m_controller(con)
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
		}
		else
		{
			std::cout << "cant lift stick, controller reset\n";
			m_controller->glow(stick->getBlockedByBegin(), stick->getBlockedByEnd());
			std::cout << "cant lift stick, controller reset finished\n";
		}
	}
	std::cout << "**Board::play m_accss.sise = " << m_accessible.size() << '\n';

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


