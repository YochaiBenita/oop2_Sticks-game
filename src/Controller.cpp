#include "Controller.h"

Controller::Controller(Board* b)//יקבל לוח לאחר שהמשתמש יבחר אם להמשיך את המשחק האחרון או להתחיל משחק חדש 
{
	if (b == nullptr)
	{
		m_board = new Board();
	}
	else //טיפול בחריגה של קריאת קובץ
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
//טיפול בחריגה של קריאת שלב ויצירת שלב
	
	//צריך לולאה כלשהי לא?
	if (m_board->play()) // if fhinished the game seccessfully
	{
		//פונקציה לעדכון נקודות?
		m_toExit = m_board->to_exit();
		delete m_board;
		m_board = nullptr;
	}
	else //end of time
	{
		//פונקציה לעדכון נקודות?
		delete m_board;
		m_board = nullptr;
	}
}


