#pragma once

#include <windows.h>

class Gamer
{
public:

	Gamer(COORD coord) : direction(RIGHT), coord{0}
	{
		this->coord.X = coord.X;
		this->coord.Y = coord.Y;

		map[coord.Y][coord.X] = 'O';

		SetConsoleCursorPosition(hd, coord);
		printf("O");
	}

	COORD getCoord()
	{
		return this->coord;
	}

	direct_t getDirection()
	{
		return direction;
	}

	void setCoord(COORD coord)
	{
		if (this->coord.X != coord.X || this->coord.Y != coord.Y)
		{
			if (map[coord.Y][coord.X] != ' ') return;
			
			map[this->coord.Y][this->coord.X] = ' ';
			SetConsoleCursorPosition(hd, this->coord);
			printf(" ");

			this->coord.X = coord.X;
			this->coord.Y = coord.Y;

			map[this->coord.Y][this->coord.X] = 'O';
			SetConsoleCursorPosition(hd, coord);
			printf("O");
		}
	}

	void action()
	{
		if (GetKeyState('D') < 0)
		{
			COORD coord = this->coord;
			coord.X++;
			setCoord(coord);

			direction = RIGHT;
		}

		if (GetKeyState('A') < 0)
		{
			COORD coord = this->getCoord();
			coord.X--;
			setCoord(coord);

			direction = LEFT;
		}

		if (GetKeyState('W') < 0)
		{
			COORD coord = this->getCoord();
			coord.Y--;
			setCoord(coord);

			direction = UP;
		}

		if (GetKeyState('S') < 0)
		{
			COORD coord = this->getCoord();
			coord.Y++;
			setCoord(coord);

			direction = DOWN;
		}

		if (GetKeyState(VK_SPACE) < 0)
		{
			int index = 0;

			for (index = 0; index < 10; index++)
				if (!bullets[index]) break;

			if (!bullets[index])
				if (direction == RIGHT || direction == LEFT)
				{
					bullets[index] = new Bullet(coord, direction);
					previous_direction = direction;
				}
				else
					bullets[index] = new Bullet(coord, previous_direction);
			
			
		}
	}

private:

	COORD coord;
	direct_t direction;
	direct_t previous_direction;

};
