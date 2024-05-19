#include <SFML/Graphics.hpp>
#include <chrono>
#include <time.h>

int main()
{
	

	auto w =sf::RenderWindow(sf::VideoMode(600, 600), "sfml");
	while (w.isOpen()) {
		auto d = sf::CircleShape(5, 360);
		d.setPosition(sf::Vector2f(100, 100));
		d.setFillColor(sf::Color::Blue);
		d.setOrigin(sf::Vector2f(5, 5));
		auto l = sf::RectangleShape(sf::Vector2f(200, 20));
		l.setPosition(sf::Vector2f(100, 100));
		l.setFillColor(sf::Color::Red);
		l.setRotation(30);
		l.setOrigin(sf::Vector2f(0, 10));

		auto r = sf::RectangleShape (l.getGlobalBounds().getSize());
		r.setPosition(l.getGlobalBounds().getPosition());
		r.setOutlineColor(sf::Color::Yellow);
		r.setOutlineThickness(5);
		r.setFillColor(sf::Color::Transparent);

		auto l2 = sf::RectangleShape(sf::Vector2f(150, 20));
		l2.setPosition(sf::Vector2f(150, 128.867));
		l2.setFillColor(sf::Color::Cyan);
		l2.setOrigin(sf::Vector2f(0, 10));
		l2.setOutlineColor(sf::Color::Black);
		l2.setOutlineThickness(1);

		auto l3 = sf::RectangleShape(sf::Vector2f(200, 20));
		l3.setPosition(sf::Vector2f(150, 148.867));
		l3.setFillColor(sf::Color::Blue);
		l3.setOrigin(sf::Vector2f(0, 10));
		l3.setOutlineColor(sf::Color::Black);
		l3.setOutlineThickness(1);

		sf::Vertex p[] = {
			sf::Vector2f(100,100),
			sf::Vector2f(273.2, 200)
		};

		//p->color(sf::Color::Green);

		w.clear(sf::Color::White);
		w.draw(l);
		w.draw(l2);
		w.draw(l3);
		w.draw(r);
		w.draw(d);
		w.draw(p, 2, sf::Lines);
		w.display();
	}
	
	return 0;
}
