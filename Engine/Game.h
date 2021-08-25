#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "Food.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	Board brd;
	Location delta_loc = {1,0};
	Snake snake;

	std::default_random_engine rng;

	Food food;
	int snakeMovementPerFrame = 30;
	int snakeMovementPeriod = 0;

	int snakeSpeedIncrement = 0;
	static constexpr int snakeSpeedPerFrame = 180;
	

	bool isGameover = false;
	bool isGameStarted = false;
};