#include "Food.h"


Food::Food(std::default_random_engine& rng , Board & b, Snake & s)
{
	CreateNewFood(rng, b, s);
}

void Food::CreateNewFood(std::default_random_engine& rng, Board & b, Snake& s)
{
	std::uniform_int_distribution<int>xDist(0, b.GetBoardWidth() - 1);
	std::uniform_int_distribution<int>yDist(0, b.GetBoardHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (s.CheckLocationForFood(newLoc));

	loc = newLoc;
}

void Food::Draw(Board & b)
{
	b.Draw(loc, foodColor);
}

const Location & Food::GetLocation() const
{
	return loc;
}
