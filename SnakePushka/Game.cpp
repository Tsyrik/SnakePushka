#include "Game.h"

Game::Game(int hardnessLvl, int fieldHight, int fieldWidth) :
	m_hardnessLvl(hardnessLvl),
	m_field(std::make_unique<PlayField>(hardnessLvl, fieldHight, fieldWidth))
{

}

void Game::NewGame()
{
	m_field->StartGame();
	m_field->Join();
}
