#pragma once
#include<string>
class GameSettings
{
private:
	int width;
	int height;
	int cellDimension;
	float snakeSpeedFactor;

public:
	GameSettings(const std::string& filename);
	int GetWidth() const;
	int GetHeight() const;
	int GetCellDimension() const;
	float GetSnakeSpeedFactor() const;

};