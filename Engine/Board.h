#pragma once
#include "Location.h"
#include "Graphics.h"
#include <assert.h>
class Board
{
private:
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int dimension = 20;

	static constexpr int x = 70;
	static constexpr int y = 50;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;

	Graphics& graphics;
public:
	Board(Graphics& gfx);
	void Draw(const Location& loc ,Color c);
	const int GetBoardWidth() const;
	const int GetBoardHeight() const;
	bool isCollided(const Location& l) const;
	void DrawBorders();
	
};