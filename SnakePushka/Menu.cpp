#include <iostream>
#include <string>
#include "Menu.h"
#include "Enums.h"


Menu::Menu() :
	m_consoleColor{ GetStdHandle(STD_OUTPUT_HANDLE) },
	m_cursorHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
}

void Menu::Start() {
	//Prepare and display greeting screen
	std::string greetings;
	greetings += "############################\n";
	greetings += "###Welcome to the SNAKE!####\n";
	greetings += "############################\n";
	greetings += "Special thanks to NOKIA 3310\n";
	greetings += "############################\n";
	greetings += "#####And Taneli Armanto#####\n";
	std::cout << greetings << std::endl;


	Enter();

	//Game initialization and restart sequence
	while (true) {
		std::cout << "Menu:" << std::endl;
		SelectColor();
		SelectDifficulty();
		HideCursor();
		system("cls");
		m_game = std::make_unique<Game>(m_speed, FieldSize::HIGHT, FieldSize::WIDTH);
		m_game->NewGame();

		ShowCursor();
		m_game.reset();
	}
}

void Menu::Enter() {
	std::cout << std::endl;
	std::cout << "Press ENTER to start";
	std::cin.get();
}

void Menu::SelectColor()
{
	//Offering player to choose screen color
	std::cout << "Select color: 1 - GREEN, 2 - RED, 3 - YELLOW, 4 - BLUE, 5 - SUPRIZE ME!: ";
	char color;
	while (true)
	{
		std::cin >> color;
		if (color < 49 || color > 53)
		{
			//If entered value is wrong
			std::cout << "Try just one of these numbers" << std::endl;
			std::cout << "1 - GREEN, 2 - RED, 3 - YELLOW, 4 - BLUE, 5 - SUPRIZE ME!: ";
			std::cin.clear();
		}
		else
		{
			//Setting one of picked color
			switch (color)
			{
			case '1':
				SetConsoleTextAttribute(m_consoleColor, Color::GREEN);
				break;
			case '2':
				SetConsoleTextAttribute(m_consoleColor, Color::RED);
				break;
			case '3':
				SetConsoleTextAttribute(m_consoleColor, Color::YELLOW);
				break;
			case '4':
				SetConsoleTextAttribute(m_consoleColor, Color::BLUE);
				break;
			case '5':
				SetConsoleTextAttribute(m_consoleColor, Color::NOKIASTYLE);
				break;
			default:
				break;
			}
			return;
		}
	}
}

void Menu::SelectDifficulty() {
	//Offering player to choose difficulty
	char speed;
	while (true) {
		std::cout << "Select difficulty: 1 - GRANDPA, 2 - KID, 3 - PRO:";
		std::cin >> speed;
		if (speed < 49 || speed > 51)
		{
			//If entered value is wrong
			std::cout << "Try just one of these numbers" << std::endl;
			std::cout << "1 - LOW, 2 - MID, 3 - HI:";
			std::cin.clear();
		}
		else
		{
			//Setting game speed
			switch (speed)
			{
			case '1':
				m_speed = Difficulty::LOW;
				break;
			case '2':
				m_speed = Difficulty::MID;
				break;
			case '3':
				m_speed = Difficulty::HI;
				break;
			default:
				break;
			}
			return;
		}
	}
}

void Menu::HideCursor() {
	GetConsoleCursorInfo(m_cursorHandle, &m_structCursorInfo);
	m_structCursorInfo.bVisible = false;
	SetConsoleCursorInfo(m_cursorHandle, &m_structCursorInfo);
}

void Menu::ShowCursor()
{
	GetConsoleCursorInfo(m_cursorHandle, &m_structCursorInfo);
	m_structCursorInfo.bVisible = true;
	SetConsoleCursorInfo(m_cursorHandle, &m_structCursorInfo);
}
