#include <SFML/Graphics.hpp>
#include <chrono>

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

		auto l2 = sf::RectangleShape(sf::Vector2f(200, 20));
		l2.setPosition(sf::Vector2f(150, 128.867));
		l2.setFillColor(sf::Color::Cyan);
		l2.setOrigin(sf::Vector2f(0, 10));

		sf::Vertex p[] = {
			sf::Vector2f(100,100),
			sf::Vector2f(273.2, 200)
		};

		//p->color(sf::Color::Green);

		w.clear();
		w.draw(l);
		w.draw(l2);
		w.draw(r);
		w.draw(d);
		w.draw(p, 2, sf::Lines);
		w.display();
	}
	
	return 0;
}
