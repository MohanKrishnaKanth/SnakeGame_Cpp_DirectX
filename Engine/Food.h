#pragma once
#include "Location.h"
#include "Snake.h"
#include "Board.h"
#include <random>

class Food
{
private:
	Location loc;
	Color c;



public:
	Food(std::default_random_engine& rng, Board& b, Snake& s);
	void CreateNewFood(std::default_random_engine& rng, Board& b, Snake& s);
	void Draw(Board& b);
	const Location& GetLocation()const;
	static constexpr Color foodColor = Colors::Red;
};