#include "GameSettings.h"
#include <fstream>
GameSettings::GameSettings(const std::string & filename)
{
	std::fstream in(filename);

	for (std::string line; std::getline(in,line);)
	{
		if (line == "[Cell Dimension]")
		{
			in >> cellDimension;
		}
		else if (line == "[Board Dimension]")
		{
			in >> width >> height;
		}
		else if (line == "[Snake SpeedFactor]")
		{
			in >> snakeSpeedFactor;
		}
		else if (line.empty())
		{
			
		}

		else
		{
			throw std::runtime_error("line is empty at " + line);
		}

	}
}

int GameSettings::GetWidth() const
{
	return width;
}

int GameSettings::GetHeight() const
{
	return height;
}

int GameSettings::GetCellDimension() const
{
	return cellDimension;
}

float GameSettings::GetSnakeSpeedFactor() const
{
	return snakeSpeedFactor;
}
