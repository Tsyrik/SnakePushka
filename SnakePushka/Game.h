#pragma once
#include <memory>
#include "PlayField.h"
#include "Enums.h"


class Game
{
public:
	Game(int hardnessLvl, int fieldHight, int fieldWidth);

	void NewGame();

private:
	std::unique_ptr<PlayField> m_field;
	int m_hardnessLvl;
	int m_direction = Direction::UP;
};

