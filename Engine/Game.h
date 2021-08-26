#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "FrameTimer.h"

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
	FrameTimer ft;
	float snakeMovementCounter = 0.0; // nanoseconds b/w frames are added as deltatime
	float snakeMovementPeriod = 0.5f; // condition for after how many nanoseconds are added per one second, we need 2 movements per second so 0.5f
	float snakeMovementPeriodMin = 0.06f; //we decrease the condition to speed up the snake so, the min of this number will make max speed
	float speedUpFactor = 0.025f; // we change the speedup by adding this additional value

	bool isGameover = false;
	bool isGameStarted = false;
};