#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <list>
using std::list;
#define Width 50
#define Height 20

enum Status{Left, Right, Up, Down};

struct Snake
{
	list<COORD> Node;
	int core = 0;
	int n;
	Status st;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}; 

struct Fruit
{
	COORD Pos;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
};



void Init(Snake &_snake, Fruit &_fruit)
{
	_snake.n = 3;
	
	for (int i = 0; i < _snake.n; i++)
	{
		COORD begin;
		begin.X = i;
		begin.Y = 0;
		_snake.Node.push_back(begin);
	}
	_snake.st = Right;
	_fruit.Pos.X = 6;
	_fruit.Pos.Y = 6;
}

void Screen(Snake _snake, Fruit _fruit)
{
	system("cls");
	for (int i = 0; i < Height; i++)
	{
		COORD map;
		map.Y = i;
		map.X = Width;
		SetConsoleCursorPosition(_snake.consoleHandle, map);
		SetConsoleTextAttribute(_snake.consoleHandle, (0 << 4) | 12);
		printf("|");
	}

	COORD pos_text;
	pos_text.X = Width + 1;
	pos_text.Y = 3;
	SetConsoleCursorPosition(_snake.consoleHandle, pos_text);
	SetConsoleTextAttribute(_snake.consoleHandle, (0 << 4) | 10);
	printf("CORE: %d", _snake.core);

	for (int i = 0; i < Width; i++)
	{
		COORD map;
		map.X = i;
		map.Y = Height;
		SetConsoleCursorPosition(_snake.consoleHandle, map);
		SetConsoleTextAttribute(_snake.consoleHandle, (0 << 4) | 12);
		printf("-");
	}
	
	for (list <COORD>::iterator i = _snake.Node.begin(); i != _snake.Node.end(); i++)
	{
		COORD test;
		test.X = i->X;
		test.Y = i->Y;
		SetConsoleCursorPosition(_snake.consoleHandle, test);
		SetConsoleTextAttribute(_snake.consoleHandle, (0 << 4) | 6);
		printf("*");
	}

	

	SetConsoleCursorPosition(_fruit.consoleHandle, _fruit.Pos);
	SetConsoleTextAttribute(_fruit.consoleHandle, (0 << 4) | 5);
	printf("O");

	
}

void Control(Snake &_snake)
{
	/*for (int i = _snake.n -1; i > 0; i--)
	{
		_snake.Node[i] = _snake.Node[i - 1];
	}*/
	

	if (_kbhit())
	{
		char key = _getch();
		if (key == 'a' || key == 'A')
			_snake.st = Left;
		else if (key == 'd' || key == 'D')
			_snake.st = Right;
		else if (key == 'w' || key == 'W')
			_snake.st = Up;
		else if (key == 's' || key == 'S')
			_snake.st = Down;
	}
	list <COORD>::iterator i = _snake.Node.begin();
	COORD NodeTemp = *i;
	if (_snake.st == Left)
		i->X--;
	else
	{
		if (_snake.st == Right)
			i->X++;
		else
		{
			if (_snake.st == Up)
				i->Y--;
			else
			{
				i->Y++;
			}
		}
	}

	_snake.Node.pop_back();
	_snake.Node.insert(++_snake.Node.begin(), NodeTemp);
}

int Handling(Snake &_snake, Fruit & _fruit)
{
	list<COORD>::iterator ibegin = _snake.Node.begin();
	
	if ((_snake.Node.begin()->X == _fruit.Pos.X) && (_snake.Node.begin()->Y == _fruit.Pos.Y))
	{
		_snake.Node.push_front(_fruit.Pos);
		if (_snake.st == Up)
			ibegin->Y--;
		else if (_snake.st == Down)
			ibegin->Y++;
		else if (_snake.st == Left)
			ibegin->X--;
		else if (_snake.st == Right)
			ibegin->X++;

		_snake.core += 5;

		list<COORD>::iterator it = _snake.Node.begin();
		
		it++;

		_fruit.Pos.X = rand() % Width ;
		_fruit.Pos.Y = rand() % Height;

		while (it!=_snake.Node.end())
		{
			if (_fruit.Pos.X == it->X && _fruit.Pos.Y == it->Y)
			{
				_fruit.Pos.X = rand() % Width;
				_fruit.Pos.Y = rand() % Height;
			}
			it++;
		}


	}
	
	if (ibegin->X < 0 || ibegin->X >= Width || ibegin->Y < 0 || ibegin->Y >= Height)
		return -1;
	
	list<COORD>::iterator test = _snake.Node.begin();
	//list<COORD>::iterator ibegin1 = _snake.Node.begin();
	//ibegin1++;
	//while (ibegin1 !=_snake.Node.end())
	//{
	//	if ((test->X == ibegin1->X) && (test->Y == ibegin1->Y))
	//		//return -1;
	//	ibegin1++;
	//}


}

int main()
{
	clock_t deltatime;
	clock_t Time;
	srand(time(NULL));
	Snake snake;
	Fruit fruit;
	Init(snake, fruit);
	
	while (1)
	{
		clock_t start = clock();
		
		Screen(snake, fruit);
		Control(snake);
		int Ghost = Handling(snake, fruit);
		if (Ghost == -1)
		{
			break;
		}
		
		clock_t finish = clock();
		deltatime = finish - start;
		Time = deltatime + 16;
		Sleep(Time);
	
		
	}

}