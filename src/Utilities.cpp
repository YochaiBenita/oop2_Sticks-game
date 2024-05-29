#include "Resources.h"
#include "Utilities.h"

void handleHover(sf::Vector2f v2f, sf::RectangleShape* buttons, int size)
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
		message.setPosition(sf::Vector2f(MESSAGE_SCREEN_SIZE.x / 2, divideScreen * (i + 1)));
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
