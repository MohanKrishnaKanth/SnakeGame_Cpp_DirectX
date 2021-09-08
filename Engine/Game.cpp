#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(settings,gfx),
	rng(std::random_device()()),
	speedUpFactor(settings.GetSnakeSpeedFactor()),
	snake({ 10,10 })
{
	brd.CreateCellType(Board::CellType::Food,snake,rng);
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
				snakeMovementCounter -= snakeMovementPeriod;

				Location nextPredictLoc = snake.NextLocationPredict(delta_loc);

				if (!brd.isCollided(nextPredictLoc) || snake.IsCollideItselfExceptTail(nextPredictLoc) ||brd.GetCellType(nextPredictLoc) == Board::CellType::Obstacle)
				{
					isGameover = true;
					//sndGameOver.Play();
					sndMusic.StopAll();
				}
				else
				{
					bool foodTaken = brd.GetCellType(nextPredictLoc) == Board::CellType::Food;
					bool poisonTaken = brd.GetCellType(nextPredictLoc) == Board::CellType::Poison;
					if (foodTaken)
					{
						snake.Grow();
						sfxEat.Play(rng, 0.8f);

					}
					snake.MoveBy(delta_loc);
					if (poisonTaken)
					{
						sfxEat.Play(rng, 0.8f);
						brd.CellConsumed(nextPredictLoc);
						snakeMovementPeriod = std::max(snakeMovementPeriod - speedUpFactor, snakeMovementPeriodMin);
					}
					if (foodTaken)
					{
						brd.CellConsumed(nextPredictLoc);
						brd.CreateCellType(Board::CellType::Food,snake,rng);
						brd.CreateCellType(Board::CellType::Obstacle,snake,rng);
						brd.CreateCellType(Board::CellType::Poison,snake,rng);
					}




				}
			}

		}
	}

	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			 sndMusic.Play(1.0f, 0.6f);
			 isGameStarted = true;
		}

	}

}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		snake.Draw(brd);
		if (isGameover)
		{
			SpriteCode::DrawGameover(330, 230, gfx);
		}
		brd.DrawBorders();
		brd.DrawCellTypes();
	}
	else
	{
		SpriteCode::TitleScreen(240, 230, gfx);
	}

}
