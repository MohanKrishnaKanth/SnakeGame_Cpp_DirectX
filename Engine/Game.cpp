#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 10,10 }),
	food(rng, brd, snake)

{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.FrameDiff();
	if (isGameStarted)
	{
		if (!isGameover)
		{
			{
				Location temp = delta_loc * -1;
				if (wnd.kbd.KeyIsPressed(VK_RIGHT))
				{
					delta_loc = { 1,0 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_LEFT))
				{
					delta_loc = { -1,0 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_UP))
				{
					delta_loc = { 0,-1 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_DOWN))
				{
					delta_loc = { 0,1 };
				}

				delta_loc = temp == delta_loc ? delta_loc * -1 : delta_loc;
			}
			

			snakeMovementCounter += dt;
			if (snakeMovementCounter>= snakeMovementPeriod)
			{
				snakeMovementCounter = 0;

				Location nextPredictLoc = snake.NextLocationPredict(delta_loc);

				if (!brd.isCollided(nextPredictLoc) || snake.IsCollideItselfExceptTail(nextPredictLoc))
				{
					isGameover = true;
				}
				else
				{
					bool isEating = nextPredictLoc == food.GetLocation();

					if (isEating)
					{
						snake.Grow();

					}
					snake.MoveBy(delta_loc);
					if (isEating)
					{
						food.CreateNewFood(rng, brd, snake);
					}
				}
			}

			snakeMovementPeriod = std::max(snakeMovementPeriod - dt * speedUpFactor, snakeMovementPeriodMin);

		}
	}

	else
	{
		isGameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}

}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		snake.Draw(brd);
		food.Draw(brd);
		if (isGameover)
		{
			SpriteCode::DrawGameover(330, 230, gfx);
		}
		brd.DrawBorders();
	}
	else
	{
		SpriteCode::TitleScreen(240, 230, gfx);
	}

}
