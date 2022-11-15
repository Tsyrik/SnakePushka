#pragma once
#include "Game.h"

class Menu {
public:
	Menu();
	void Start();

private:
	void Enter();
	void SelectColor();
	void SelectDifficulty();
	void HideCursor();
	void ShowCursor();

private:
	int m_speed;
	std::unique_ptr<Game> m_game;
	HANDLE m_consoleColor;
	HANDLE m_cursorHandle;
	CONSOLE_CURSOR_INFO m_structCursorInfo;
};