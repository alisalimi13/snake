// In The Name Of Allah

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct p
{
	int x, y;
};

const int x = 20;
const int y = 40;
const int max = 40;
int a[x][y] = { 0 };
bool state = true;
int hx, hy, tx, ty, sd, sl;
p s[max];

void setHT()
{
	hx = s[0].x;
	hy = s[0].y;
	tx = s[sl - 1].x;
	ty = s[sl - 1].y;
}

void wallCreate()
{
	for (int i = 0; i < y; i++)
	{
		a[0][i] = 1;
		a[x - 1][i] = 1;
	}
	for (int i = 0; i < x; i++)
	{
		a[i][0] = 1;
		a[i][y - 1] = 1;
	}

	return;
}

void setFood()
{
	while (true)
	{
		srand(time(0));

		int n = rand() % x;
		int m = rand() % y;
		
		if (a[n][m] == 0)
		{
			a[n][m] = 2;
			break;
		}
	}

	return;
}

void setSnake()
{
	sl = 3;
	srand(time(0));
	sd = rand() % 4 + 1;
	s[0].x = hx = rand() % (x - 6) + 3;
	s[0].y = hy = rand() % (y - 6) + 3;
	a[hx][hy] = 3;

	switch (sd)
	{
	case 1:
		a[hx][hy + 1] = 4;
		a[hx][hy + 2] = 4;
		s[1].x = hx;
		s[1].y = hy + 1;
		s[2].x = hx;
		s[2].y = hy + 2;
		break;

	case 2:
		a[hx - 1][hy] = 4;
		a[hx - 2][hy] = 4;
		s[1].x = hx - 1;
		s[1].y = hy;
		s[2].x = hx - 2;
		s[2].y = hy;
		break;

	case 3:
		a[hx][hy - 1] = 4;
		a[hx][hy - 2] = 4;
		s[1].x = hx;
		s[1].y = hy - 1;
		s[2].x = hx;
		s[2].y = hy - 2;
		break;

	case 4:
		a[hx + 1][hy] = 4;
		a[hx + 2][hy] = 4;
		s[1].x = hx + 1;
		s[1].y = hy;
		s[2].x = hx + 2;
		s[2].y = hy;
		break;
	}

	setHT();

	return;
}

void printMap()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			switch (a[i][j])
			{
			case 0:
				cout << " ";
				break;

			case 1:
				cout << char(219);
				break;

			case 2:
				cout << "+";
				break;

			case 3:
				cout << char(1);
				break;

			case 4:
				cout << "O";
				break;
			}
		}
		cout << endl;
	}
}

void printState()
{
	cout << endl;
	cout << "Snake Length : " << sl << endl;
	cout << "Winner Length : " << max << endl;
	return;
}

void moveSnake()
{
	for (int i = sl - 1 ; i > 0 ; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;

	}

	switch ( sd )
	{
	case 1:
		s[0].y--;
		break;

	case 2:
		s[0].x++;
		break;

	case 3:
		s[0].y++;
		break;

	case 4:
		s[0].x--;
		break;
	}

	setHT();

	return;
}

void SnakeInMap(int head, int body, int tail)
{
	a[s[0].x][s[0].y] = head;
	for (int i = 1; i < sl - 1; i++)
	{
		a[s[i].x][s[i].y] = body;
	}
	a[s[sl - 1].x][s[sl - 1].y] = tail;

	return;
}

void growUp()
{
	s[sl].x = s[sl - 1].x;
	s[sl].y = s[sl - 1].y;
	sl++;
	setHT();

	return;
}

void gameState()
{
	if (a[hx][hy] == 1 || a[hx][hy] == 4 || sl >= max)
		state = false;

	return;
}

void foodState()
{
	if (a[hx][hy] == 2)
	{
		growUp();
		setFood();
	}
}

void refresh()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	wallCreate();
	setSnake();
	setFood();
	printMap();

	while (!_kbhit());
	while (state)
	{
		SnakeInMap(3, 4, 4);
		refresh();
		printMap();
		printState();
		if (_kbhit())
		{
			switch (_getch())
			{
			case 75:
				if (sd != 3)
					sd = 1;
				break;

			case 80:
				if (sd != 4)
					sd = 2;
				break;

			case 77:
				if (sd != 1)
					sd = 3;
				break;

			case 72:
				if (sd != 2)
					sd = 4;
				break;

			default:
				break;
			}
		}
		SnakeInMap(3, 4, 0);
		moveSnake();
		foodState();
		gameState();
		Sleep(100);
	}
	cout << endl << (sl >= max ? "You Win :)" : "You Lose :(") << endl;
	cout << "\nPress Enter To Exit...";
	while ( !(getchar() == '\n') );
	return EXIT_SUCCESS;
}