#include "Board.h"
#include "Snake.h"


Board::Board(const GameSettings& settings,Graphics & gfx)
		:width(settings.GetWidth()),
		height(settings.GetHeight()),
		dimension(settings.GetCellDimension()),
		cellLocations(width * height, CellType::Empty),
		graphics(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int offset_x = x + borderWidth;
	const int offset_y = y + borderWidth;

	graphics.DrawRectWithDim(loc.x*dimension + offset_x + cellPadding, loc.y*dimension + cellPadding + offset_y, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}


const int Board::GetBoardWidth() const
{
	return width;
}

const int Board::GetBoardHeight() const
{
	return height;
}

bool Board::isCollided(const Location& l) const
{
	return l.x >= 0 && l.x < width &&
		l.y >= 0 && l.y < height;
}

void Board::DrawBorders() 
{
	int left = x;
	int top = y;
	int bottom = top + (borderWidth + borderPadding * 2) + height * dimension;
	int right = left + (borderWidth + borderPadding * 2) + width * dimension;

	// x,y are as one point
	{
		//top
		// drawing from rightside to left so x will be
		//x --> x to right (i.e with padding)
		//y --> y to y + bordewidth


		Location topLeft, topRight;
		topLeft.x = x;
		topLeft.y = y;

		topRight.x = right;
		topRight.y = y + borderWidth;

		graphics.DrawRectWithPoints(topLeft.x, topLeft.y, topRight.x, topRight.y,Colors::Blue);

	}

	{
		//right
		// drawing from rightside to left so x will be

		//x --> (right - borderwidth) to right(i.e with padding)
		//y --> y to bottom (i.e with padding)

		Location topRight, bottomRight;

		topRight.x = right - borderWidth; 
		topRight.y = y;

		bottomRight.x = right;
		bottomRight.y = bottom;

		graphics.DrawRectWithPoints(topRight.x, topRight.y, bottomRight.x, bottomRight.y, Colors::Blue);
		
	}


	{
		// drawing from rightside to left so x will be
		// x -->  (x - borderwidth) to x
		// y -->  y  to bottom (i.e with padding)

		//left
		Location topLeft, bottomLeft;

		topLeft.x = x - borderWidth;
		topLeft.y = y;

		bottomLeft.x = x;
		bottomLeft.y = bottom;

		graphics.DrawRectWithPoints(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, Colors::Blue);

	}



	{
		//bottom
		// x --> x to right
		// y --> y to y + borderwidth

		//     but this bottom so we need padding
		// y --> bottom to (bottom + borderwidth)


		Location bottomLeft, bottomRight;

		bottomLeft.x = x;
		bottomLeft.y = bottom;

		bottomRight.x = right;
		bottomRight.y = bottom + borderWidth;

		graphics.DrawRectWithPoints(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, Colors::Blue);

	}
}

void Board::CreateCellType(CellType ct,const Snake& snake, std::default_random_engine& rng)
{

	std::uniform_int_distribution<int> xDist(0, GetBoardWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetBoardHeight() - 1);
	Location l;
	do
	{
		l = { xDist(rng),yDist(rng) };
		
	} while (snake.CheckLocationToGenerate(l) || GetCellType(l) != CellType::Empty);


	cellLocations[l.y * width + l.x] = ct;

}


void Board::DrawCellTypes()
{

	for (int y = 0; y < height ; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			switch (GetCellType({x,y}))
			{
			case Board::Empty:
				break;
			case Board::Food:
				DrawCell({ x,y }, Colors::Red);
				break;
			case Board::Poison:
				DrawCell({ x,y }, { 64,8,64 });
				break;
			case Board::Obstacle:
				DrawCell({ x,y }, Colors::LightGray);
				break;
			default:
				break;
			}


			
		}
	}
}



void Board::CellConsumed(const Location & l)
{
	cellLocations[l.y * width + l.x] = CellType::Empty;
}

Board::CellType Board::GetCellType(const Location& l)  const
{
	return cellLocations[l.y * width + l.x];
}


