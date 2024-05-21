#include "Controller.h"

Controller::Controller(Board* b)//���� ��� ���� ������� ���� �� ������ �� ����� ������ �� ������ ���� ��� 
{
	if (b == nullptr)
	{
		m_board = new Board();
	}
	else //����� ������ �� ����� ����
	{
		m_board = b;
	}
}

Controller::~Controller()
{
	if (m_board != nullptr)
		delete m_board;
}

void Controller::run(sf::RenderWindow& m_wind) 
{
//����� ������ �� ����� ��� ������ ���
	
	//���� ����� ����� ��?
	if (m_board->play()) // if fhinished the game seccessfully
	{
		//������� ������ ������?
		m_toExit = m_board->to_exit();
		delete m_board;
		m_board = nullptr;
	}
	else //end of time
	{
		//������� ������ ������?
		delete m_board;
		m_board = nullptr;
	}
}


