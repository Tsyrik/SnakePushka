#pragma once
#include <memory>
#include <thread>
#include <windows.h>
#include "Snake.h"
#include "SimpleApple.h"

class PlayField
{
public:
	PlayField(int hardnessLvl, int fieldHight, int fieldWidth);

	void StartGame();
	void Join();

private:
	void GetInput();
	void DrawField();
	void CheckCollisions();
	bool IsSnakeBodyOrBorder(int x, int y);

private:
	bool m_gameOver;
	int m_fieldHight;
	int m_fieldWidth;
	int m_hardnessLvl;
	int m_score = 0;

	std::string m_fieldDisplay;

	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<SimpleApple> m_food;
	std::unique_ptr<std::thread> m_inputSignals;
	std::unique_ptr<std::thread> m_drawField;

	HANDLE m_cursorHandle;
	COORD m_cursorInitPosition;
};
