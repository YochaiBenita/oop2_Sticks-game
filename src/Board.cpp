#include "Board.h"

Board::Board()
{
	int x = rand() % 30 + 20;//num of sticks betwean 20-49
	for (int i = 0; i < x; i++) 
	{
		m_sticksList.push_front(Stick());
	}

	auto stick = m_sticksList.begin();

	for (int i = 0; i < x; i++)
	{
		stick->findAllIntersections(m_sticksList ,stick++);
	}

	//checking all intersections
	stick = m_sticksList.begin();

	for (int i = 0; i < x; i++)
	{
		if (stick->isAccessible())
		{
			m_accessible.insert({ stick->getScore(), &(*stick) });
		}
	}
}

bool Board::play()
{
	return false;
}

bool Board::to_exit()
{
	return false;
}
