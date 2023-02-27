#include "Logic.h"

std::random_device rndd;

void start()
{
	Field field(25);
	Snake snake;

	printArea(field);

	delete field[snake.getLast()->getX()][snake.getLast()->getY()];
	field[snake.getLast()->getX()][snake.getLast()->getY()] = snake.getLast();

	randomGenerateApple(field);

	bool finished = false;
	char direction = char(Right_Arrow),
		lockedDirection = direction;

	while (!finished)
	{
		printField(field);

		if (_kbhit() && _getch())
		{
			direction = _getch();

			if (directionValidation(direction) && !directionOppose(lockedDirection, direction))
				lockedDirection = direction;
		}

		finished = move(field, snake, lockedDirection);

		Sleep(25);
	}	

	StartCursor(0, field.getSize() + 2);
}

void printArea(Field& field)
{
	StartCursor();

	cout << char(201);
	for (size_t i = 0; i < field.getSize(); i++)
		cout << char(205) << char(205);
	cout << char(187) << endl;

	for (short i = 1; i <= field.getSize(); i++)
	{
		StartCursor(0, i);
		cout << char(186);

		StartCursor(field.getSize() * 2 + 1, i);
		cout << char(186);
	}

	StartCursor(0, field.getSize() + 1);

	cout << char(200);
	for (size_t i = 0; i < field.getSize(); i++)
		cout << char(205) << char(205);
	cout << char(188);
}

void printField(Field& field)
{
	ShowConsoleCursor(FALSE);
	for (unsigned short i = 0; i < field.getSize(); i++)
	{
		for (short b = 0; b < field.getSize(); b++)
		{
			StartCursor(b * 2 + 1, i + 1);

			if (!field[i][b]->isInvisible())
			{
				char block = field[i][b]->getBlock();
				cout << block << block;
			}
			else
				cout << "  ";
		}
	}
}

void randomGenerateApple(Field& field)
{
	Apple* apple = new Apple();

	unsigned short x = 0, y = 0;

	do
	{
		x = rndd() % field.getSize();
		y = rndd() % field.getSize();
	} while (!field[x][y]->isInvisible());

	delete field[x][y];

	field[x][y] = apple;
}

bool move(Field& field, Snake& snake, char direction)
{
	if (directionValidation(direction))
	{
		unsigned short
			x = snake.getLast()->getX(),
			y = snake.getLast()->getY(),
			xprev = x,
			yprev = y;

		snake.getLast()->setDirection(direction);

		switchDirection(direction, x, y);

		if (x == field.getSize())
			x = 0;
		else if (x == USHRT_MAX)
			x = field.getSize() - 1;

		if (y == field.getSize())
			y = 0;
		if (y == USHRT_MAX)
			y = field.getSize() - 1;

		//if (x < field.getSize() && y < field.getSize())
		//{
		if (field[x][y]->isInvisible() && !field[x][y]->isLogicElement())
		{
			Snake_Game::SnakePart* snakePartLast = snake.getLast();

			swap(field[snakePartLast->getX()][snakePartLast->getY()], field[x][y]);

			snakePartLast->setCoords(x, y);
			snakePartLast->setDirection(direction);

			//		Direction in this type of move don`t use
			//char ch = ' ';
			//for (size_t i = 0; i < snake.size() - 1; i++)
			//{
			//	ch = snake[i]->getDirection();
			//	snake[i]->setDirection(ch);
			//}

			for (int i = (int)snake.size() - 2; i >= 0; i--)
			{
				x = xprev;
				y = yprev;

				swap(field[snake[i]->getX()][snake[i]->getY()], field[x][y]);

				xprev = snake[i]->getX();
				yprev = snake[i]->getY();

				snake[i]->setCoords(x, y);
				//snake[i]->setDirection(direction);
			}

			return false;
		}
		else if (field[x][y]->isDestroyable())
		{
			// Here we can use dynamic cast to class Increaser and get points from element
			delete field[x][y];

			Snake_Game::SnakePart* snakePart = new Snake_Game::SnakePart();

			snakePart->setCoords(x, y);
			//snakePart->setDirection(direction);

			snake.push_back(snakePart);

			field[x][y] = snake.getLast();

			randomGenerateApple(field);

			return false;
		}
		//}
	}
	return true;
}

bool directionValidation(char direction)
{
	return direction == char(Up_Arrow) || direction == char(Down_Arrow)
		|| direction == char(Right_Arrow) || direction == char(Left_Arrow);
}

bool directionOppose(char from, char to)
{
	int diff = abs(from - to);

	return diff == 2 || diff == 8;
}

void switchDirection(char direction, unsigned short& x, unsigned short& y, bool reverse)
{
	switch (direction)
	{
	case Down_Arrow:
		if (!reverse)
			++x;
		else
			--x;
		break;

	case Up_Arrow:
		if (!reverse)
			--x;
		else
			++x;
		break;

	case Right_Arrow:
		if (!reverse)
			++y;
		else
			--y;
		break;

	case Left_Arrow:
		if (!reverse)
			--y;
		else
			++y;
		break;

	default: break;
	}
}

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;

	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;

	cci.bVisible = bShow;

	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;

	return TRUE;
}

void StartCursor(const SHORT x, const SHORT y)
{
	COORD position{ x + 10, y + 5 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsole, position);
}