#include "Controller.h"
#include <iostream>

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
		//
		m_wind.draw(m_backgraund);
		
		auto delta_time = m_clock.restart();
		m_timer -= delta_time.asSeconds();

		if (m_blinking)
		{
			std::cout << "blinking\n";
			sf::sleep(sf::seconds(0.7));
			std::cout << "sleep 0.7\n";
			(*m_glowingCurr)->glow(false);
			std::cout << "glow off\n";
			m_glowingCurr++;
			std::cout << "it ++\n";
			if (m_glowingCurr == m_glowingEnd)
			{
				std::cout << "inside if end\n";
				m_blinking = false;
				continue;
			}
			std::cout << "not end\n";
			(*m_glowingCurr)->glow(true);
			std::cout << "glow on\n";
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

				if (m_backgraund.getGlobalBounds().contains(mousePosition)){
					m_board.play(m_wind, mousePosition);
				}
				else{
					//check if one of the bottons was prassed
				}
			}
		}

		m_board.draw(m_wind);

		m_wind.display();
	}
}

void Controller::glow(std::list<Stick*>::iterator curr, std::list<Stick*>::iterator end)
{
	m_blinking = true;
	m_glowingCurr = curr;
	m_glowingEnd = end;
}


