#pragma once
#include "IFood.h"

class GoldenApple : public IFood
{
public:
	GoldenApple(int scores, int addLength, std::string& fruitImg);
	~GoldenApple();

private:
	int m_scores;
	int m_addLength;
	std::string m_fruitImg;
};

GoldenApple::GoldenApple(int scores, int addLength, std::string& fruitImg)
{
}

GoldenApple::~GoldenApple()
{
}