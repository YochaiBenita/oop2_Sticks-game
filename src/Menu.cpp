#include "Menu.h"
#include <iostream>

Menu::Menu()
{

}

void Menu::show_menu()
{
	m_wind.create(sf::VideoMode(900, 500), "menu");
	m_wind.clear(sf::Color::White);
	 //מוזיקה אם נרצה

	while (m_wind.isOpen())
	{
		m_wind.clear();
		m_wind.draw(m_background);

		draw_buttons(m_wind);

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
				int option = handle_click(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

				switch (option)
				{
				case 0:
					m_controller = &Controller();
					m_controller->run(m_wind);
					m_controller->reset_controller();
					break;
				case 1:
					try
					{
						m_controller = &Controller("Stics");
					}
					catch (std::exeption exp)
					{
						std::cout << exp.what() << '\n';
						m_controller = &Controller();
					}
					m_controller->run(m_wind);
					m_controller->reset_controller();
					break;
				case 2:
					show_help();
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

void Menu::show_help()
{
	m_wind.clear(sf::Color::White);

	m_wind.clear();
	m_background.setTexture(*Resources::getInstance().getBackground(1));
	m_wind.draw(m_background);
	m_background.setTexture(*Resources::getInstance().getBackground(0));
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


int Menu::handle_click(sf::Vector2f v2f) const
{
	for (int i = 0; i < NUM_OF_BUTTONS-2; i++)
	{
		if (m_button[i].getGlobalBounds().contains(v2f))
		{
			return i;
		}
	}
	return -1;
}

void Menu::draw_buttons(sf::RenderWindow& wind) const
{
	for (int i = 0; i < NUM_OF_BUTTONS-2; i++)
	{
		wind.draw(m_button[i]);
	}
}
