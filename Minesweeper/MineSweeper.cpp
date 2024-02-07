#include <conio.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "mygraphics.h"

const int Rows = 5;
const int Cols = 5;

using namespace std;

COLORREF windowColor = RGB(12, 12, 12);
COLORREF whiteColor = RGB(250, 250, 250);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define ESCAPE 27

class MineSweeper
{
public:

	MineSweeper()
	{
	}
	~MineSweeper()
	{
	}

	void print_actual_Array(char actaulArray[][Cols]);
	void actual_Array(char actualArray[][Cols]);

	int RandforRow(int r);
	int RandforCol(int c);

	void print_play_Board(char playBoard[][Cols]);
	void play_Board(char playBoard[][Cols]);

	void playGame(char actualArray[][Cols],char playBoard[][Cols]);
	void print_play_Board(char actualArray[][Cols], char playBoard[][Cols]);


	void setMines(char actualArray[][Cols]);

};

void MineSweeper::print_actual_Array(char actaulArray[][Cols])
{
	cout << "The Actual Array is: " << endl;

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			cout << actaulArray[i][j] << " ";
		}
		cout << endl;
	}
}

void MineSweeper::actual_Array(char actualArray[][Cols])
{
	char elements = '1';

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			actualArray[i][j] = elements;
		}
		elements++;
	}

	print_actual_Array(actualArray);
}

int MineSweeper::RandforRow(int r = 5)
{
	srand(time(0));
	
	return rand() % r;
}

int MineSweeper::RandforCol(int c = 5)
{
	rand();

	return rand() % c;
}

void MineSweeper::print_play_Board(char playBoard[][Cols])
{
	cout << endl;
	cout << "The Play Board is: " << endl;

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			cout << playBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void MineSweeper::play_Board(char playBoard[][Cols])
{

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			playBoard[i][j] = 'x';
		}
	}

	print_play_Board(playBoard);
}

void MineSweeper::setMines(char actualArray[][Cols])
{
	actual_Array(actualArray);
	

	for (int i = 0; i < 5; i++)
	{
		int c = RandforRow();
		Sleep(1000);
		int d = RandforCol();
		
		actualArray[c][d] = 'm';	
	}

	print_actual_Array(actualArray);
}

void MineSweeper::print_play_Board(char actualArray[][Cols], char playBoard[][Cols])
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			cout << playBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void MineSweeper::playGame(char actualArray[][Cols], char playBoard[][Cols])
{
	actual_Array(actualArray);
	play_Board(playBoard);
	setMines(actualArray);

	int i, j;

	while (true)
	{
		cout << "Enter The Coordinates (x,y) : ";
		cin >> i; cin >> j;
		cout << endl;

		if ((actualArray[i][j] != 'm') and (playBoard[i][j] == 'x'))
		{
				playBoard[i][j] = actualArray[i][j];
				print_play_Board(actualArray, playBoard);
		}

		else if ((actualArray[i][j] != 'm') and (playBoard[i][j] != 'x'))
		{
			cout << "Location Already Exposed: " << endl;
			cout << "Please Re-Enter the Coordinates (x,y) : " << endl;
		}

		else if (actualArray[i][j] == 'm')
		{
			cout << "Sorry! You lost the game, a mine has exploded at location (" << i << "," << j << ")." << endl;
			break;
		}
	}
}

void showMenu(bool addResume = false)
{
	int x = 400;
	int y = 100;
	int menuItem = 1;

	// In case it's a call from pause, change these values
	// Also set default selection
	if (addResume)
	{
		x = 350;
		menuItem = 0;
		myDrawText(x - 20, y + 30, 25, (char*)"->", whiteColor, windowColor);	
	}
	else
		myDrawText(x - 20, y + 60, 25, (char*)"->", whiteColor, windowColor);

	while (true)
	{
		int key = 0;

		myDrawText(x - 30, y - 30, 65, (char*)"B R I C K   B R E A K E R", whiteColor, windowColor);

		if (addResume)
			myDrawText(x, y + 30, 25, (char*)"Resume", whiteColor, windowColor);

		myDrawText(x, y + 60, 25, (char*)"Start New Game", whiteColor, windowColor);
		myDrawText(x, y + 90, 25, (char*)"Load Saved Game", whiteColor, windowColor);
		myDrawText(x, y + 120, 25, (char*)"Score History", whiteColor, windowColor);
		myDrawText(x, y + 150, 25, (char*)"Exit", whiteColor, windowColor);
		myDrawText(x - 35, y + 210, 15, (char*)"Use Up / Down keys to change", whiteColor, windowColor);
		myDrawText(x - 35, y + 240, 15, (char*)"Press Enter to select", whiteColor, windowColor);

		key = _getch();

		// if user has pressed up / down arrow keys
		if (key == 224)
		{
			switch ((key = _getch()))
			{
			case KEY_UP:
				if (addResume)
				{
					if (menuItem >= 1)
						menuItem--;
				}
				else
				{
					if (menuItem > 1)
						menuItem--;
				}
				break;
			case KEY_DOWN:
				if (menuItem < 4)
					menuItem++;
				break;
			default:
				break;
			}
		}
		// If user has pressed ENTER
		else if (key == 13)
		{
			if (menuItem == 0)
			{
				system("cls");
				return;
			}
			else if (menuItem == 1)
			{
				system("cls");
				setup();
				return;
			}
			else if (menuItem == 2)
			{
				// TODO : Load game from file
				return;
			}
			else if (menuItem == 3)
			{
				//scoreHistory();
			}

			else if (menuItem == 4)
				exit(3);
		}

		// Logic to indicate selection 
		if (menuItem == 0)
		{
			myDrawText(x - 20, y + 30, 25, (char*)"->", whiteColor, windowColor);
			myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", windowColor, windowColor);
		}
		else if (menuItem == 1)
		{
			myDrawText(x - 20, y + 30, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 60, 25, (char*)"->", whiteColor, windowColor);
			myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", windowColor, windowColor);
		}
		else if (menuItem == 2)
		{
			myDrawText(x - 20, y + 30, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 90, 25, (char*)"->", whiteColor, windowColor);
			myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", windowColor, windowColor);
		}
		else if (menuItem == 3)
		{
			myDrawText(x - 20, y + 30, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 120, 25, (char*)"->", whiteColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", windowColor, windowColor);
		}
		else if (menuItem == 4)
		{
			myDrawText(x - 20, y + 30, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", whiteColor, windowColor);
		}
	}
}

int main()
{
	char arr[Rows][Cols];
	char brr[Rows][Cols];

	MineSweeper game;
	//game.actual_Array(array);
	//game.play_Board(array);

	game.playGame(arr, brr);


}