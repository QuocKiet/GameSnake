#include <stdio.h>
#include <Windows.h>
//#include <time.h>
#include <conio.h>
//#include <stdlib.h>

#define width 50
#define height 20

enum TT{ L, R, U, D };

int main()
{
	TT T = L;
	COORD coord;
	coord.X = 5;
	coord.Y = 5;
	int i = 0;
	int j = 1;
	char key;
	while (true)
	{
		
		system("cls");

		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(consoleHandle, coord);
		SetConsoleTextAttribute(consoleHandle, (0 << 4) | 5);
		
		printf("Hello");

		if (_kbhit())
		{
			key = _getch();
			if (key == 'a' || key == 'A')
				T = L;
			else if (key == 'd' || key == 'D')
				T = R;
			else if (key == 'w' || key == 'W')
				T = U;
			else if (key == 's' || key == 'S')
				T = D;
		}
		if (T == L)
			coord.X--;
		else
		{
			if (T == R)
				coord.X++;
			else
			{
				if (T == U)
					coord.Y--;
				else
				{
					coord.Y++;
				}
			}
		}

		if (coord.X == width)
			T = L;
		else
		{
			if (coord.X == 0)
				T = R;
			else
			{
				if (coord.Y == 0)
					T = D;
				else
				{
					if (coord.Y == height)
						T = U;
				}
			}
		}
		Sleep(100);
	}
	
	return 0;
	
}