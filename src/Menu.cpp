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

void printMessage(const std::vector<std::string> mes)
{
	auto window = sf::RenderWindow(sf::VideoMode(MESSAGE_SCREEN_SIZE.x, MESSAGE_SCREEN_SIZE.y), "message");
	auto rect = sf::RectangleShape(MESSAGE_SCREEN_SIZE);
	rect.setTexture(Resources::getInstance().getBackground(0));
	window.draw(rect);

	auto message = sf::Text();
	message.setFont(*Resources::getInstance().getFont());
	message.setCharacterSize(50);

	float divideScreen = MESSAGE_SCREEN_SIZE.y / (mes.size() + 1);

	for (int i = 0; i < mes.size(); i++)
	{
		message.setString(mes[i]);
		message.setOrigin(sf::Vector2f(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2));
		message.setPosition(sf::Vector2f(MESSAGE_SCREEN_SIZE.x / 2, divideScreen*(i+1)));
		window.draw(message);
	}

	window.display();

	auto event = sf::Event();
	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;
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
		printMessage(std::vector<std::string>{exp.what()});
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
