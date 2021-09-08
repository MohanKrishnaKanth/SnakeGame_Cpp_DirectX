#pragma once
#include "Location.h"
#include "Graphics.h"
#include <assert.h>
#include<random>
#include<vector>
#include "GameSettings.h"

class Board
{
public:
	enum CellType
	{
		Empty,
		Food,
		Poison,
		Obstacle
	};

private:
	 int width;
	 int height;
	 int dimension;

	static constexpr int x = 70;
	static constexpr int y = 50;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;

	std::vector<CellType> cellLocations;

	Graphics& graphics;
public:
	Board(const GameSettings& settings,Graphics& gfx);
	void DrawCell(const Location& loc ,Color c);
	const int GetBoardWidth() const;
	const int GetBoardHeight() const;
	bool isCollided(const Location& l) const;
	void DrawBorders();
	void CreateCellType(CellType ct,const class Snake& snake, std::default_random_engine& rng);
	
	CellType GetCellType(const Location& l) const;
	void DrawCellTypes();
	void CellConsumed(const Location& l);
};