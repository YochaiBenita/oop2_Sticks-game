#include <SFML/Graphics.hpp>
#include <vector>

class Stick
{
public:

private:
	int m_blockedBy = 0;
	std::vector<Stick*> m_blocking;
	sf::Line line;
	//or
	sf::RectangleShape line1;
	sf::vector2f m_startPoint;
};