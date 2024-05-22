#include "Controller.h"

Controller::Controller(Board* b)//���� ��� ���� ������� ���� �� ������ �� ����� ������ �� ������ ���� ��� 
{
	//board craeting, and updating all privates
	m_backgraund.setSize(BOARD_SIZE);
	m_backgraund.setPosition(sf::Vector2f(300, 0));
	m_backgraund.setOutlineColor(sf::Color::Blue);
	m_backgraund.setOutlineThickness(5);
	m_backgraund.setFillColor(sf::Color::White);



	if (b == nullptr)
	{
		m_board = &Board();
	}
	else //����� ������ �� ����� ����
	{
		m_board = b;
	}
}

Controller::~Controller()
{
	//if (m_board != nullptr)
	//	delete m_board;
}

void Controller::run(sf::RenderWindow& m_wind) 
{
	while (m_wind.isOpen())
	{
		m_wind.clear();
		//print info
		m_wind.draw(m_backgraund);

		m_board->play(m_wind);

		m_wind.display();

	}





//����� ������ �� ����� ��� ������ ���
	
	//���� ����� ����� ��?
	if (m_board->play(m_wind)) // if fhinished the game seccessfully
	{
		//print winner
	}
	else //end of time
	{
		//
		//print "losser" or save to file
	}
}


