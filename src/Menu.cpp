#include "Menu.h"
#include <iostream>
#include <exception>
#include "Resources.h"

void handleHover(sf::Vector2f v2f, sf::RectangleShape* buttons, int size) //global function
{
	for (int i = 0; i < size; i++)
	{
		if (buttons[i].getGlobalBounds().contains(v2f))
		{
			buttons[i].setScale(1.1, 1.1);
		}
		else
		{
			buttons[i].setScale(1, 1);
		}
	}
}

Menu::Menu()
{
	m_background.setTexture(Resources::getInstance().getBackground(0));
	m_background.setSize(SCREEN_SIZE);
	m_controller = nullptr;

	for (int i = 0; i < NUM_OF_BUTTONS_MENU; i++)
	{
		m_button[i].setSize(sf::Vector2f(300, 120));
		m_button[i].setOrigin(sf::Vector2f(150, 50));
		m_button[i].setPosition(sf::Vector2f(450, 120 * (i + 1)));
		m_button[i].setTexture(Resources::getInstance().getTextureButtons(i));	
	}
}

Menu::~Menu()
{
	if (m_controller)
	{
		delete m_controller;
	}
}

void Menu::showMenu()
{
	m_wind.create(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "sticks");

	while (m_wind.isOpen())
	{
		m_wind.clear(sf::Color::White);
		m_wind.draw(m_background);

		sf::Vector2i mousePos = sf::Mouse::getPosition(m_wind);
		sf::Vector2f mousePosF(mousePos.x, mousePos.y);

		handleHover(mousePosF, m_button, NUM_OF_BUTTONS_MENU);
		drawButtons(m_wind);

		m_wind.display();

		if (auto event = sf::Event(); m_wind.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_wind.close();
				break;

			case sf::Event::MouseButtonReleased:
			{
				int option = handleClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

				switch (option)
				{
				case 0:
					newGame();
					break;
				case 1:
					loadGame();
					break;
				case 2:
					showHelp();
					break;
				case 3:
					m_wind.close();
					break;
				}
			}
			}
		}

	}
}

int Menu::handleClick(sf::Vector2f v2f) const
{
	for (int i = 0; i < NUM_OF_BUTTONS_MENU; i++)
	{
		if (m_button[i].getGlobalBounds().contains(v2f))
		{
			return i;
		}
	}
	return -1;
}

void Menu::drawButtons(sf::RenderWindow& wind) const
{
	for (int i = 0; i < NUM_OF_BUTTONS_MENU; i++)
	{
		wind.draw(m_button[i]);
	}
}

void Menu::newGame()
{
	m_controller = new Controller();
	m_controller->run(m_wind);
	delete m_controller;
	m_controller = nullptr;
}

void Menu::loadGame()
{
	try
	{
		m_controller = new Controller(FILE_NAME);
		m_controller->run(m_wind);
		delete m_controller;
		m_controller = nullptr;
	}
	catch (std::exception& exp)
	{
		auto errorWind = sf::RenderWindow(sf::VideoMode(ERROR_SCREEN_SIZE.x, ERROR_SCREEN_SIZE.y), "error");
		errorWind.draw(m_background);
		auto massage = sf::Text();
		massage.setString(exp.what());
		massage.setFont(*Resources::getInstance().getFont());
		massage.setOrigin(sf::Vector2f(massage.getGlobalBounds().width / 2, massage.getGlobalBounds().height / 2));
		massage.setPosition(sf::Vector2f(ERROR_SCREEN_SIZE.x / 2, ERROR_SCREEN_SIZE.y / 2));

		
		errorWind.draw(massage);
		errorWind.display();

		auto event = sf::Event();
		while (errorWind.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				errorWind.close();
				break;
			}
		}
	}
}

void Menu::showHelp()
{
	m_wind.clear(sf::Color::White);

	m_wind.clear();
	m_background.setTexture(Resources::getInstance().getBackground(1));

	m_wind.draw(m_background);
	
	m_background.setTexture(Resources::getInstance().getBackground(0));
	m_wind.display();

	while (true)
	{
		if (auto event = sf::Event(); m_wind.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_wind.close();
				return;
			case sf::Event::MouseButtonReleased:
				return;
			}
		}
	}
}
