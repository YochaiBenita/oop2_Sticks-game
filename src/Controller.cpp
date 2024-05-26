#include "Controller.h"
#include <iostream>
#include "Resources.h"

Controller::Controller(): m_board(this)
{
	m_background.setTexture(Resources::getInstance().getBackground(0));
	m_background.setSize(sf::Vector2f(900, 600));

	m_boardBackground.setSize(BOARD_SIZE);
	m_boardBackground.setPosition(sf::Vector2f(300, 0));
	m_boardBackground.setOutlineColor(sf::Color::Black);
	m_boardBackground.setOutlineThickness(5);
	m_boardBackground.setFillColor(sf::Color::Color(255,255,255, 50));

}

Controller::Controller(std::string fileName): m_board(this, fileName)
{
	m_background.setTexture(Resources::getInstance().getBackground(0));

	m_boardBackground.setSize(BOARD_SIZE);
	m_boardBackground.setPosition(sf::Vector2f(300, 0));
	m_boardBackground.setOutlineColor(sf::Color::Black);
	m_boardBackground.setOutlineThickness(5);
	m_boardBackground.setFillColor(sf::Color::Transparent);
}

Controller::~Controller()
{
	//if (m_board != nullptr)
	//	delete m_board;
}

void Controller::run(sf::RenderWindow& m_wind) 
{
	while (m_wind.isOpen() && m_timer > 0 && !m_board.finished())
	{
		m_wind.clear(sf::Color::White);
		m_wind.draw(m_background);

		//print info
		//printing score, timer, hint, save 
		//
		m_wind.draw(m_boardBackground);
		
		auto delta_time = m_clock.restart();
		m_timer -= delta_time.asSeconds();

		if (m_blinking)
		{
			sf::sleep(sf::seconds(0.7));
			(*m_glowingCurr)->glow(false);
			++m_glowingCurr;
			if (m_glowingCurr == m_glowingEnd)
			{
				m_blinking = false;
				continue;
			}
			(*m_glowingCurr)->glow(true);
		}
		else if (auto event = sf::Event(); m_wind.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				m_wind.close();
				exit(EXIT_FAILURE);
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto mousePosition = m_wind.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

				if (m_boardBackground.getGlobalBounds().contains(mousePosition)){
					m_board.play(m_wind, mousePosition);
				}
				else{
					//check if one of the bottons was prassed
				}
			}
		}

		m_board.draw(m_wind);

		//debug(m_wind);

		m_wind.display();
	}
}

void Controller::glow(std::list<Stick*>::iterator curr, std::list<Stick*>::iterator end)
{
	m_blinking = true;
	m_glowingCurr = curr;
	m_glowingEnd = end;
}

void Controller::addToScore(int score)
{
	m_score += score;
}

//void Controller::debug(sf::RenderWindow& m_wind)
//{
//	m_board.debug(m_wind);
//}


