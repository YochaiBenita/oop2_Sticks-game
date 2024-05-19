#include <SFML/Graphics.hpp>
#include <list>

class Stick
{
public:
	Stick();


private:
	std::list<Stick*> m_blocking;
	std::list<Stick*> mblockedBy;
	
	sf::RectangleShape line1;
	sf::Vector2f m_startPoint;
};