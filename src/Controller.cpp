#include "Controller.h"
#include <iostream>
#include <string>
#include "Menu.h"

Controller::Controller() : m_board(this)
{
	resetSFMLComponents();
}

Controller::Controller(std::string fileName): m_board(this, fileName)
{
	resetSFMLComponents();
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

		draw_data(m_wind);
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

				if (m_boardBackground.getGlobalBounds().contains(mousePosition)) {
					m_board.play(m_wind, mousePosition);
				}
				else {
					int option = handleClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

					switch (option)
					{
					case 0:
						//hint
						addToScore(-20);

						break;
					case 1:
						//save

						break;
					}
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
		wind.draw(m_data[i]);
	}

	for (int i = 0; i < NUM_OF_BUTTONS_BOARD; i++)
	{
		wind.draw(m_buttonsGame[i]);
	}
}

void Controller::addToScore(int score)
{
	m_score += score;
}

//void Controller::debug(sf::RenderWindow& m_wind)
//{
//	m_board.debug(m_wind);
//}
int Controller::handleClick(sf::Vector2f v2f) const
{
	for (int i = 0; i < NUM_OF_BUTTONS_MENU; i++)
	{
		if (m_buttonsGame[i].getGlobalBounds().contains(v2f))
		{
			return i;
		}
	}
	return -1;
}

void Controller::resetSFMLComponents()
{
	for (int i = 0; i < NUM_OF_DATA; i++)
	{
		m_data[i].setFillColor(sf::Color::White);
		m_data[i].setCharacterSize(40);
		m_data[i].setFont(*Resources::getInstance().getFont());
		m_data[i].setOrigin(sf::Vector2f(m_data[i].getGlobalBounds().width / 2, m_data[i].getGlobalBounds().height / 2));
		m_data[i].setPosition(sf::Vector2f(10, 20 + 100 * i));
	}

	m_background.setTexture(Resources::getInstance().getBackground(0));
	m_background.setSize(sf::Vector2f(900, 600));

	m_boardBackground.setSize(BOARD_SIZE);
	m_boardBackground.setPosition(sf::Vector2f(300, 0));
	m_boardBackground.setOutlineColor(sf::Color::Black);
	m_boardBackground.setOutlineThickness(5);
	m_boardBackground.setFillColor(sf::Color::Color(255, 255, 255, 50));

	for (int i = 0; i < NUM_OF_BUTTONS_BOARD; i++)
	{
		m_buttonsGame[i].setSize(sf::Vector2f(100, 100));
		m_buttonsGame[i].setPosition(sf::Vector2f(30 + i * 100, 480));
		m_buttonsGame[i].setTexture(Resources::getInstance().getTextureBoardButtons(i));
	}
}

//void Controller::hint()
//{
//	for (int i = 0; i < (m_board.getAccessibleStics()); i++)
//	{
//
//	}
//}

