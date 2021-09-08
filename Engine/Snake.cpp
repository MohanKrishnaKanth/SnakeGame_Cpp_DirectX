#include "Snake.h"

Snake::Snake(const Location& loc)
{
	constexpr int totalColors = 4;
	constexpr Color bodyColors[totalColors]=
	{
		{10,100,32}, {10,130,48}, {10,160,48},{10,130,48}
	};

	for (int i = 0; i < size; ++i)
	{
		segments[i].InitBody((bodyColors[i%totalColors]));
	}
	segments[0].InitHead(loc);
}

void Snake::Draw(Board & b)
{
	for (int i = 0; i < currentSegment; ++i)
	{
		segments[i].Draw(b);
	}
}

void Snake::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	for (int i = currentSegment - 1; i > 0; --i)
	{
		segments[i].ShiftSegment(segments[i - 1].GetLocation());
	}
	segments[0].MoveHead(delta_loc);
}

void Snake::Grow()
{
	if (currentSegment < size)
	{
		++currentSegment;
	}
}

//location& is not using because the scope of newloc will be gone after calculated. so we sending as value
const Location Snake::NextLocationPredict(const Location& delta_loc) const
{
	Location newloc = segments[0].GetLocation();
	newloc.Add(delta_loc);
	return newloc;
}

bool Snake::IsCollideItselfExceptTail(const Location& delta_loc) const
{
	for (int i = 1; i < currentSegment; ++i)
	{
		if(segments[i].GetLocation() == delta_loc)
		{
			return true;
		}
	}

	return false;
}

bool Snake::CheckLocationToGenerate(const Location& loc) const
{
	for (int i = 0; i < currentSegment; ++i)
	{
		if (segments[i].GetLocation() == loc)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::Draw(Board& d)
{
	d.DrawCell(loc, c);
}

void Snake::Segment::InitHead(const Location& l)
{
	loc = l;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color in_c)
{
	c = in_c;
}

void Snake::Segment::MoveHead(const Location& l)
{
	loc.Add(l);
}

void Snake::Segment::ShiftSegment(const Location& l)
{
	loc = l;
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
