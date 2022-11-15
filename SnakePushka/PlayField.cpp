#include <string>
#include <iostream>
#include <conio.h>
#include "PlayField.h"
#include "Enums.h"

PlayField::PlayField(int hardnessLvl, int fieldHight, int fieldWidth) :
	m_fieldHight(fieldHight),
	m_fieldWidth(fieldWidth),
	m_hardnessLvl(hardnessLvl),
	m_snake(std::make_unique<Snake>(fieldHight / 2, fieldWidth / 2)),
	m_food(std::make_unique<SimpleApple>(fieldHight, fieldWidth)),
	m_cursorHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
	m_snake->SetDirection(Direction::UP);
	m_inputSignals = std::make_unique<std::thread>(&PlayField::GetInput, this);
	m_drawField = std::make_unique<std::thread>(&PlayField::DrawField, this);
}

void PlayField::StartGame()
{
	m_gameOver = false;

	while (!m_gameOver) {

		CheckCollisions();
		std::this_thread::sleep_for(std::chrono::milliseconds(m_hardnessLvl));
	}

}

void PlayField::DrawField()
{
	while (!m_gameOver) {
		for (int x = 0; x <= m_fieldWidth + 1; ++x)
		{
			m_fieldDisplay += (char)(219);
			m_fieldDisplay += (char)(219);
		}
		m_fieldDisplay += "\n";
		for (int y = 1; y <= m_fieldHight + 1; ++y)
		{
			for (int x = 0; x <= m_fieldWidth + 1; ++x)
			{
				if (x == 0) {
					m_fieldDisplay += (char)(219);
					m_fieldDisplay += (char)(219);
				}
				else if (x == m_fieldWidth + 1) {
					m_fieldDisplay += (char)(219);
					m_fieldDisplay += (char)(219);
					m_fieldDisplay += "\n";
				}
				else {
					if (m_snake->GetHeadX() == x && m_snake->GetHeadY() == y)
					{
						m_fieldDisplay += (char)(219);
						m_fieldDisplay += (char)(219);
					}
					else  if (m_food->GetCoordX() == x && m_food->GetCoordY() == y)
					{
						m_fieldDisplay += "[]";
					}
					else
					{
						bool print = true;
						auto tail = m_snake->GetTail();
						for (size_t k = 1; k < tail->size(); ++k)
						{
							if ((*tail)[k].first == x && (*tail)[k].second == y)
							{
								m_fieldDisplay += (char)(219);
								m_fieldDisplay += (char)(219);
								print = false;
								break;
							}
						}
						if (print)
						{
							m_fieldDisplay += "  ";
						}
					}
				}
			}
		}
		for (int x = 0; x <= m_fieldWidth + 1; ++x)
		{
			m_fieldDisplay += (char)(219);
			m_fieldDisplay += (char)(219);
		}
		m_fieldDisplay += "\n";
		m_fieldDisplay += "SCORE: ";
		m_fieldDisplay += std::to_string(m_score);

		//Set cursor to start
		SetConsoleCursorPosition(std::ref(m_cursorHandle), std::ref(m_cursorInitPosition));

		std::cout << m_fieldDisplay << std::endl;
		m_fieldDisplay = "";
		std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
	}
}

void PlayField::GetInput()
{
	while (!m_gameOver) {
		if (_kbhit())
		{
			switch (_getch())
			{
			case 75:
				if (m_snake->GetDirection() != Direction::RIGHT)
				{
					m_snake->SetDirection(Direction::LEFT);
				}
				break;
			case 77:
				if (m_snake->GetDirection() != Direction::LEFT)
				{
					m_snake->SetDirection(Direction::RIGHT);
				}
				break;
			case 72:
				if (m_snake->GetDirection() != Direction::DOWN)
				{
					m_snake->SetDirection(Direction::UP);
				}
				break;
			case 80:
				if (m_snake->GetDirection() != Direction::UP)
				{
					m_snake->SetDirection(Direction::DOWN);
				}
				break;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
	}
}

bool PlayField::IsSnakeBodyOrBorder(int x, int y)
{
	bool isBodyOrBorder = false;
	for (size_t i = 1; i < m_snake->GetTail()->size(); ++i) {
		if (x == (*m_snake->GetTail())[i].first && y == (*m_snake->GetTail())[i].second)
		{
			isBodyOrBorder = true;
		}
	}

	if (x <= 0 || x >= m_fieldWidth + 1 ||
		y <= 0 || y >= m_fieldHight + 1) {
		isBodyOrBorder = true;
	}

	return isBodyOrBorder;
}

void PlayField::CheckCollisions()
{
	//Check if reach apple
	if (m_snake->GetHeadX() == m_food->GetCoordX() && m_snake->GetHeadY() == m_food->GetCoordY()) {
		m_snake->AteFood(m_food->GetCoordX(), m_food->GetCoordY());

		while (IsSnakeBodyOrBorder(m_food->GetCoordX(), m_food->GetCoordY()))
		{
			m_food->RespawnAnApple();
		}

		switch (m_hardnessLvl)
		{
		case Difficulty::HI:
			m_score += 300;
			break;
		case Difficulty::MID:
			m_score += 200;
			break;
		case Difficulty::LOW:
			m_score += 100;
			break;
		}
	}

	m_snake->Move();

	//Check if hit tail
	m_gameOver = IsSnakeBodyOrBorder(m_snake->GetHeadX(), m_snake->GetHeadY());

}

void PlayField::Join()
{
	m_inputSignals->join();
	m_drawField->join();
}
