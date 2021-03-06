#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "FrameTimer.h"
#include "SoundEffect.h"
#include "GameSettings.h"

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
	GameSettings settings = "Settings.txt";
	Board brd;
	Location delta_loc = {1,0};
	Snake snake;

	std::default_random_engine rng;

	FrameTimer ft;
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	Sound sndMusic = Sound(L"Sounds\\Music_Loop.wav", Sound::LoopType::AutoFullSound);
	//Sound sndGameOver = Sound(L"Sounds\\Gameover.wav");


	float snakeMovementCounter = 0.0; // nanoseconds b/w frames are added as deltatime
	float snakeMovementPeriod = 0.5f; // condition for after how many nanoseconds are added per one second, we need 2 movements per second so 0.5f
	float snakeMovementPeriodMin = 0.06f; //we decrease the condition to speed up the snake so, the min of this number will make max speed
	float speedUpFactor; // we change the speedup by adding this additional value

	bool isGameover = false;
	bool isGameStarted = false;
};