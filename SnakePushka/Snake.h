#pragma once
#include <vector>
#include <memory>

class Snake
{
public:
	Snake(int coordinate_x, int coordinate_y);
	void AteFood(int x, int y);
	void Move();
	void SetDirection(int direction);
	int GetHeadX();
	int GetHeadY();
	int GetDirection();
	std::shared_ptr<std::vector<std::pair<int, int>>> GetTail();

private:
	void MoveSnake(int x, int y);

private:
	int m_direction;
	std::shared_ptr<std::vector<std::pair<int, int>>> m_coordinates;
};

