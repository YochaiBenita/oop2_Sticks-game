#include "Board.h"

Board::Board()
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
		stick = std::find_if(stick, m_sticksList.end(), [](std::list<Stick>::iterator i) {return i->isAccessible(); });
		if (stick != m_sticksList.end())
		{
			m_accessible.insert({ stick->getScore(), &(*stick) });
			stick++;
		}
	}
}

Board::Board(std::string)
{
	//reading from file end throwing exeption
}

void Board::play(sf::RenderWindow& m_wind)
{
	auto event = sf::Event();

	while (m_wind.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			m_wind.close();
			exit(EXIT_FAILURE);
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			auto mousePosition = m_wind.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			auto stick = std::find_if(m_sticksList.begin(), m_sticksList.end(), [mousePosition](auto stick) {return stick.isPressed(mousePosition); });
			if (stick != m_sticksList.end()) {
				stick->handleClick();
			}
			//----------------------------
		}

	}
}


void Board::draw(sf::RenderWindow& m_wind) const
{
	std::for_each(m_sticksList.rbegin(), m_sticksList.rend(), [&m_wind](auto stick) {m_wind.draw(stick.getRect()); });

}


