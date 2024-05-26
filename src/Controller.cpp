#include "Controller.h"
#include <iostream>
#include <string>
#include "Resources.h"


Controller::Controller(): m_board(this)
{
	m_backgraund.setSize(BOARD_SIZE);
	m_backgraund.setPosition(sf::Vector2f(300, 0));
	m_backgraund.setOutlineColor(sf::Color::Black);
	m_backgraund.setOutlineThickness(5);
	m_backgraund.setFillColor(sf::Color::Yellow);

}

Controller::Controller(std::string fileName): m_board(this, fileName)
{
	m_backgraund.setSize(BOARD_SIZE);
	m_backgraund.setPosition(sf::Vector2f(300, 0));
	m_backgraund.setOutlineColor(sf::Color::Black);
	m_backgraund.setOutlineThickness(5);
	m_backgraund.setFillColor(sf::Color::Yellow);
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
		//print info
		//printing score, timer, hint, save 
		draw_data(m_wind);
		m_wind.draw(m_backgraund);
		
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
		else 
			if (auto event = sf::Event(); m_wind.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				m_wind.close();
				exit(EXIT_FAILURE);
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto mousePosition = m_wind.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

				if (m_backgraund.getGlobalBounds().contains(mousePosition)){
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

void Controller::draw_data(sf::RenderWindow& wind)
{
	m_data[0].setString("TIME: " + std::to_string((int)m_timer));
	m_data[1].setString("ACCESSIBLE: " + std::to_string(m_board.getAccessibleStics()));
	m_data[2].setString("REMAINED: " + std::to_string(m_board.getRemainedSticks()));
	m_data[3].setString("COLLECTED: " + std::to_string(m_board.getCollectedSticks()));
	m_data[4].setString("SCORE: " + std::to_string(m_score));

	for (int i = 0; i < NUM_OF_DATA; i++)
	{
		m_data[i].setFillColor(sf::Color::Black);
		m_data[i].setCharacterSize(40);
		m_data[i].setFont(*Resources::getInstance().getFont());
		m_data[i].setOrigin(sf::Vector2f(m_data[i].getGlobalBounds().width / 2, m_data[i].getGlobalBounds().height / 2));
		m_data[i].setPosition(sf::Vector2f(10, 20 + 100 * i));

		wind.draw(m_data[i]);
	}
}

//void Controller::debug(sf::RenderWindow& m_wind)
//{
//	m_board.debug(m_wind);
//}


