#include <time.h>
#include <cstdlib>
#include "SimpleApple.h"

SimpleApple::SimpleApple(int boardHight, int boardWidth) :
	m_boardHight(boardHight-4),
	m_boardWidth(boardWidth-4)
{
	srand(time(NULL));
	m_coordX = 2 + rand() % m_boardWidth;
	m_coordY = 2 + rand() % m_boardHight;
}

int SimpleApple::GetCoordX()
{
	return m_coordX;
}

int SimpleApple::GetCoordY()
{
	return m_coordY;
}

void SimpleApple::RespawnAnApple()
{
	srand(time(NULL));
	m_coordX = rand() % m_boardWidth;
	m_coordY = rand() % m_boardHight;
}