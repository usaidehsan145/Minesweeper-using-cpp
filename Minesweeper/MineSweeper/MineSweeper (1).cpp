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
int turns = 0;
COLORREF windowColor = RGB(12, 12, 12);
COLORREF whiteColor = RGB(255, 140, 0);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define ESCAPE 27

class MineSweeper
{
protected:

	int rows;
	int cols;
	int mines;
	int gameOver;

public:

	MineSweeper()
	{
		rows = 0;
		cols = 0;
		mines = 0;
		gameOver = 0;
	}

	MineSweeper(int r, int c, int m,int g)
	{
		rows = r;
		cols = c;
		mines = m;
		gameOver = g;
	}
	~MineSweeper()
	{
	}


	virtual void playGame(char actualArray[][Cols], char playBoard[][Cols]) = 0;
	

	void showMenu(char actualArray[][Cols], char playBoard[][Cols], bool addResume);
	void gameInstructions();

public:

	int RandforRow(int r);
	int RandforCol(int c);

	void setRows(int r);
	int getRows();

	void setCols(int c);
	int getCols();

	void setMines(int m);
	int getMines();

	void setgameOver(int g);
	int getgameOver();

};

class realArray :public MineSweeper
{
public:

	void print_actual_Array(char actaulArray[][Cols]);
	void actual_Array(char actualArray[][Cols]);
	void setMines_in(char actualArray[][Cols]);
	
};

class playArray :public realArray
{
	void play_Board(char playBoard[][Cols]);
	void print_play_Board(char playBoard[][Cols]);
	void playGame(char actualArray[][Cols], char playBoard[][Cols]);
};

void MineSweeper::setMines(int m)
{
	mines = m;
}

int MineSweeper::getMines()
{
	return mines;
}

void MineSweeper::setRows(int r)
{
	rows = r;
}

int MineSweeper::getRows()
{
	return rows;
}                                                              

void MineSweeper::setCols(int c)
{
	cols = c;
}

int MineSweeper::getCols()
{
	return cols;
}

void MineSweeper::setgameOver(int g)
{
	gameOver = g;
}

int MineSweeper::getgameOver()
{
	return gameOver;
}

void realArray::print_actual_Array(char actaulArray[][Cols])
{
	actaulArray[getRows()][getCols()];
	cout << endl << endl;
	cout << "Location of Mines (FOR EVALUATION PURPOSES): " << endl << endl;

	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getCols(); j++)
		{
			cout << actaulArray[i][j] << " ";
		}
		cout << endl;
	}
}

void realArray::actual_Array(char actualArray[][Cols])
{
	actualArray[getRows()][getCols()];

	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getCols(); j++)
		{
			actualArray[i][j] = ' ';
		}
	}
	
}

int MineSweeper::RandforRow(int r = 0)
{
	r = getRows();

	srand(time(0));

	return rand() % r;
}

int MineSweeper::RandforCol(int c = 0)
{
	c = getCols();

	rand();

	return rand() % c;
}
void MineSweeper::gameInstructions()
{
	int x = 400;
	int y = 100;

	myDrawText(x, y + 30, 25, (char*)"-> Chose a random location and enter it", whiteColor, windowColor);
	myDrawText(x, y + 60, 25, (char*)"-> Your location should be mine free", whiteColor, windowColor);
	myDrawText(x, y + 90, 25, (char*)"-> In case you step on the mine, you will lose the game", whiteColor, windowColor);
	myDrawText(x, y + 120, 25, (char*)"-> Your Target is to explore all mine free locations", whiteColor, windowColor);
	myDrawText(x, y + 150, 25, (char*)"-> Location (0,0) is always mine free", whiteColor, windowColor);
	myDrawText(x, y + 180, 25, (char*)"-> Number Of Turns Multplied by 10 is equal to your Earned Score", whiteColor, windowColor);
	myDrawText(x, y + 210, 25, (char*)"-> NOTE: MINES SHOWN IN THE START FOR EVALUATION PURPOSE ONLY", whiteColor, windowColor);
	myDrawText(x, y + 240, 25, (char*)"-> CHOOSE MEDIUM DIFFICULTY as an ideal case for EVALUATION", whiteColor, windowColor);
	myDrawText(x, y + 270, 25, (char*)"-> Have a Good Hunt :) ", whiteColor, windowColor);
}

void playArray::print_play_Board(char playBoard[][Cols])
{
	playBoard[getRows()][getCols()];

	cout << endl;
	cout << "The Play Board is: " << endl;

	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getCols(); j++)
		{
			cout << playBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void playArray::play_Board(char playBoard[][Cols])
{

	playBoard[getRows()][getCols()];

	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getCols(); j++)
		{
			playBoard[i][j] = 'x';
		}
	}

	print_play_Board(playBoard);
}

void realArray::setMines_in(char actualArray[][Cols])
{
	actual_Array(actualArray);

	for (int i = 0; i < getMines(); i++)
	{
		int c = RandforRow();
		Sleep(1800);
		int d = RandforCol();
		Sleep(1800);

		if (c == 0 && d == 0)
		{
			i--;
		}
		else
		{
			actualArray[c][d] = 'm';
		}
	}

	print_actual_Array(actualArray);
}

void playArray::playGame(char actualArray[][Cols], char playBoard[][Cols])
{
	actual_Array(actualArray);
	play_Board(playBoard);
	setMines_in(actualArray);

	int x = 400;
	int y = 100;

	int fin = 0;
	bool flag = true;
	int i, j;

	while (fin<=getgameOver())
	{
		cout << "Enter The Coordinates (x,y) : ";
		cin >> i; cin >> j;
		cout << endl;
		turns++;
		char count = '0';
		
		////////////////////////////////////////////////////////////////

		if ((actualArray[i + 1][j] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i - 1][j] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i][j + 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i][j - 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i + 1][j + 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i + 1][j - 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i - 1][j + 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if ((actualArray[i - 1][j - 1] == 'm') && (playBoard[i][j] == 'x'))
		{
			count++;
		}
		if (actualArray[i][j] == 'm')
		{
			system("cls");
			cout << endl << " MINE EXPLODED AT LOCATION (" << i << "," << j << ")." << endl;
			myDrawText(x, y, 25, (char*)"SORRY, YOU LOST!", whiteColor, windowColor);
			cout << "Your Earned Score is " << turns * 10;
			turns = 0;
			Sleep(5000);
			system("cls");
			break;
			
		}
		
		

		actualArray[i][j] = count;
		playBoard[i][j] = count;

		print_play_Board(playBoard);
		system("cls");
		print_play_Board(playBoard);

		fin++;
	}

	
}

void MineSweeper::showMenu(char actualArray[][Cols], char playBoard[][Cols], bool addResume = false)
{
	int x = 400;
	int y = 100;
	int menuItem = 1;
	int difficultyLevel = 1;

Escape_From_DifficultyLevel:
Escape_From_GameInstructions:

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

		myDrawText(x - 30, y - 30, 65, (char*)"M  I  N  E  S  W  E  E  P  E  R", whiteColor, windowColor);
		myDrawText(x, y + 60, 25, (char*)"Start New Game", whiteColor, windowColor);
		myDrawText(x, y + 90, 25, (char*)"Game Instructions", whiteColor, windowColor);
		/*myDrawText(x, y + 120, 25, (char*)"Score History", whiteColor, windowColor);*/
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
			else if (menuItem == 1)                              //////////////////////////////////////
			{
				system("cls");
				myDrawText(x - 20, y + 60, 25, (char*)"->", whiteColor, windowColor);

				while (true)
				{
					int key = 0;

					myDrawText(x - 30, y - 30, 65, (char*)"SELECT DIFFICULTY LEVEL", whiteColor, windowColor);

					myDrawText(x, y + 60, 25, (char*)"Easy", whiteColor, windowColor);
					myDrawText(x, y + 90, 25, (char*)"Medium", whiteColor, windowColor);
					myDrawText(x, y + 120, 25, (char*)"Professional", whiteColor, windowColor);

					key = _getch();

					// if user has pressed up / down arrow keys
					if (key == 224)
					{
						switch ((key = _getch()))
						{
						case KEY_UP:
							if (difficultyLevel > 0)
								difficultyLevel--;
							break;
						case KEY_DOWN:
							if (difficultyLevel < 3)
								difficultyLevel++;
							break;
						default:
							break;
						}
					}
					else if (key == ESCAPE)
					{
						goto Escape_From_DifficultyLevel;
					}
					// If user has pressed ENTER
					else if (key == 13)
					{
						if (difficultyLevel == 1)                      //easy
						{
							setRows(7);
							setCols(7);
							setMines(9);
							setgameOver(40);
						}
						else if (difficultyLevel == 2)                 //medium
						{
							setRows(5);
							setCols(5);
							setMines(5);
							setgameOver(20);
						}
						else if (difficultyLevel == 3)                 //professional
						{
							setRows(3);
							setCols(3);
							setMines(5);
							setgameOver(4);
						}

						system("cls");
						playGame(actualArray, playBoard);
					}

					if (difficultyLevel == 1)
					{
						myDrawText(x - 20, y + 60, 25, (char*)"->", whiteColor, windowColor);
						myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
						myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
					}
					else if (difficultyLevel == 2)
					{
						myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
						myDrawText(x - 20, y + 90, 25, (char*)"->", whiteColor, windowColor);
						myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
					}
					else if (difficultyLevel == 3)
					{
						myDrawText(x - 20, y + 60, 25, (char*)"->", windowColor, windowColor);
						myDrawText(x - 20, y + 90, 25, (char*)"->", windowColor, windowColor);
						myDrawText(x - 20, y + 120, 25, (char*)"->", whiteColor, windowColor);
					}
				}
			}
			else if (menuItem == 2)
			{
				// Instruction
				system("cls");
				Sleep(500);
				gameInstructions();
				Sleep(6000);
				system("cls");
				if (key == ESCAPE)
				{
					goto Escape_From_GameInstructions;
				}
			}
			
			else if (menuItem == 3)
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
			myDrawText(x - 20, y + 120, 25, (char*)"->", windowColor, windowColor);
			myDrawText(x - 20, y + 150, 25, (char*)"->", whiteColor, windowColor);
		}
	}
}

int main()
{
	char arr[Rows][Cols];
	char brr[Rows][Cols];

	playArray game;

	game.showMenu(arr, brr);

}