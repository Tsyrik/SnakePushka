#pragma once

class SimpleApple
{
public:
	SimpleApple(int boardHight, int boardWidth);

	int GetCoordX();
	int GetCoordY();

	void RespawnAnApple();

private:
	int m_coordX;
	int m_coordY;

	int m_boardHight;
	int m_boardWidth;
};
