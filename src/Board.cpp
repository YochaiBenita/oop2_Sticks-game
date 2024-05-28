#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Controller.h"
#include "InvalidFileException.h"
#include "InvalidContentFileException.h"

std::multimap<int, Stick* , std::greater<int>> Board::m_accessible;

Board::Board()
{
	int x = rand() % 30 + 20;//num of sticks betwean 20-49

	for (int i = 0; i < x; i++) 
	{
		m_sticksList.push_front(Stick());
	}

	findAllIntersections();
}

Board::Board(Controller* con, const std::string fileName)
{
	auto file = std::ifstream(fileName);
	int temp;

	if (!file.is_open())
	{
		throw InvalidFileException();
	}

	std::string line;
	std::getline(file, line);
	std::istringstream iss(line);

	iss >> temp;
	con->addToScore(temp);

	iss >> temp;
	con->resetTimer(temp);

	iss >> temp;
	m_collected = temp;

	while (std::getline(file, line))
	{
		m_sticksList.push_back(Stick(line));
	}

	findAllIntersections();
}

Board::~Board()
{
	m_accessible.clear();
}

void Board::findAllIntersections()
{
	auto stick = m_sticksList.begin();

	for (int i = 0; i < m_sticksList.size(); i++)
	{
		stick->findAllIntersections(m_sticksList, ++stick);
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

void Board::play(Controller* controller, const sf::Vector2f& mousePosition)
{
	auto stick = std::find_if(m_sticksList.begin(), m_sticksList.end(), [mousePosition](auto stick) {return stick.isPressed(mousePosition); });
	if (stick != m_sticksList.end()) 
	{
		if (stick->handleClick())
		{
			controller->addToScore(removeAccessible(&(*stick)));
			m_sticksList.remove(*stick);
			m_collected++;
		}
		else
		{
			controller->updateBlinking(&(*stick));
			controller->addToScore(WORNG_STICK_FINE);
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

void Board::writeSticks(std::ofstream& file) const
{
	std::for_each(m_sticksList.begin(), m_sticksList.end(), [&file](auto stick) {file << stick << '\n'; });
}

std::multimap<int, Stick*>::iterator Board::getAccessibleBegin() const
{
	return m_accessible.begin();
}

std::multimap<int, Stick*>::iterator Board::getAccessibleEnd() const
{
	return m_accessible.end();
}

int Board::removeAccessible(Stick* stick)
{
	int score = 0;
	auto it = std::find_if(m_accessible.begin(), m_accessible.end(),
		[stick](const auto pair) {return pair.second == stick; });
	if (it != m_accessible.end())
	{
		score = it->first;
		it = m_accessible.erase(it);
	}
	return score;

}


