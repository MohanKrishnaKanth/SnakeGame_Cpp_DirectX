#include "Board.h"

Board::Board(Graphics & gfx)
	  :graphics(gfx)
{

}

void Board::Draw(const Location& loc, Color c)
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

		graphics.DrawRectWithPoints(topLeft.x, topLeft.y, topRight.x, topRight.y,Colors::Gray);

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

		graphics.DrawRectWithPoints(topRight.x, topRight.y, bottomRight.x, bottomRight.y, Colors::Gray);
		
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

		graphics.DrawRectWithPoints(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, Colors::Gray);

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

		graphics.DrawRectWithPoints(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, Colors::Gray);

	}
}
