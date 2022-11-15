#include "Snake.h"
#include "Enums.h"

Snake::Snake(int coordinate_x, int coordinate_y) :
	m_coordinates(std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>{std::make_pair(coordinate_x, coordinate_y)}))
{

}

void Snake::Move()
{
	switch (m_direction)
	{
	case Direction::LEFT: MoveSnake(-1, 0);
		break;
	case Direction::RIGHT: MoveSnake(1, 0);
		break;
	case Direction::UP: MoveSnake(0, 1);
		break;
	case Direction::DOWN: MoveSnake(0, -1);
		break;
	}
}

int Snake::GetHeadX()
{
	return (*m_coordinates)[0].first;
}

int Snake::GetHeadY()
{
	return (*m_coordinates)[0].second;
}

void Snake::MoveSnake(int x, int y) {

	for (int i = m_coordinates->size(); i > 0; --i) {

		if (i == 1) {
			(*m_coordinates)[0].first += x;
			(*m_coordinates)[0].second -= y;
			return;
		}
		int flag = true;
		if (i == m_coordinates->size()) {
			for (size_t j = 0; j < m_coordinates->size() - 1; ++j) {
				if ((*m_coordinates)[m_coordinates->size() - 1].first == (*m_coordinates)[j].first &&
					(*m_coordinates)[m_coordinates->size() - 1].second == (*m_coordinates)[j].second) {
					flag = false;
				}
			}
			if (flag) {
				(*m_coordinates)[i - 1].first = (*m_coordinates)[i - 2].first;
				(*m_coordinates)[i - 1].second = (*m_coordinates)[i - 2].second;
			}
		}
		else {
			(*m_coordinates)[i - 1].first = (*m_coordinates)[i - 2].first;
			(*m_coordinates)[i - 1].second = (*m_coordinates)[i - 2].second;
		}
	}
}

void Snake::AteFood(int x, int y)
{
	m_coordinates->push_back(std::pair<int, int>{ x, y });
}


std::shared_ptr<std::vector<std::pair<int, int>>> Snake::GetTail()
{
	return m_coordinates;
}

void Snake::SetDirection(int direction)
{
	m_direction = direction;
}

int Snake::GetDirection()
{
	return m_direction;
}
