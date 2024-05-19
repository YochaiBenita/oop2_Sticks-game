#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include "Stick.h"

class Board
{
public:
	Board();
	bool intersect();
private:
	std::list<Stick> m_sticksList;
	std::multimap<int, Stick*> m_accessible;

};