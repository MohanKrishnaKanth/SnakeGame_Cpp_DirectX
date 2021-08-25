#pragma once
class Location
{
public:
	int x;
	int y;
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	bool operator==(const Location& l) const
	{
		return x == l.x && y == l.y;
	}

	const Location operator * (int i)
	{
		x *= i;
		y *= i;
		return { x,y };
	}
};
