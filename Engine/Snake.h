#pragma once
#include"Location.h"
#include"Graphics.h"
#include"Board.h"

class Snake 
{	
private:
	class Segment
	{
	private:
		Location loc;
		Color c;
	public:
		void Draw(Board& d);
		void InitHead( const Location& l) ;
		void InitBody(Color c);
		void MoveHead(const Location& l);
		void ShiftSegment(const Location& l);
		const Location& GetLocation() const;
	};

private:
	Location loc;
	static constexpr int size = 100;
	Segment segments[size];
	int currentSegment = 1;

public:
	Snake(const Location& l) ;
	void Draw(Board& b);
	void MoveBy(const Location& delta_loc);
	void Grow();
	const Location NextLocationPredict(const Location& delta_loc) const;
	bool IsCollideItselfExceptTail(const Location& delta_loc) const;
	bool CheckLocationToGenerate(const Location& loc) const;
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
};