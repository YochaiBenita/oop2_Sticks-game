#include "Board.h"
#include <iostream>
#include <fstream>
#include "Controller.h"
#include "InvalidFileException.h"
#include "InvalidContentFileException.h"

Board::Board(Controller* con) : m_controller(con)
{
	int x = rand() % 30 + 20;//num of sticks betwean 20-49
	for (int i = 0; i < x; i++) 
	{
		m_sticksList.push_front(Stick());
	}

	auto stick = m_sticksList.begin();

	for (int i = 0; i < x; i++)
	{
		stick->findAllIntersections(m_sticksList ,stick++);
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

void Board::play(sf::RenderWindow& m_wind, const sf::Vector2f& mousePosition)
{
	auto stick = std::find_if(m_sticksList.begin(), m_sticksList.end(), [mousePosition](auto stick) {return stick.isPressed(mousePosition); });
	if (stick != m_sticksList.end()) 
	{
		if (stick->handleClick())
		{
			//revome from accsseible
			m_sticksList.remove(*stick);
		}
		else
		{
			m_controller->glow(stick->getBlockingList().begin(), stick->getBlockingList().end());
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


