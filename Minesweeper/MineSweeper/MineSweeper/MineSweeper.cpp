#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>

const int Rows = 5;
const int Cols = 5;

using namespace std;

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
	char elements = '0';

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
		int d = RandforCol();
		
		actualArray[c][d] = 9;	
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

	int i, j;

	while (true)
	{
		cout << "Enter The Coordinates (x,y) : ";
		cin >> i; cin >> j;
		cout << endl;

		if ((actualArray[i][j] != 'm' or actualArray[i][j] != 'M') and (playBoard[i][j] == 'x'))
		{
				playBoard[i][j] = actualArray[i][j];
				print_play_Board(actualArray, playBoard);
		}

		else if ((actualArray[i][j] != 'm' or actualArray[i][j] != 'M') and (playBoard[i][j] != 'x'))
		{
			cout << "Location Already Exposed: " << endl;
			cout << "Please Re-Enter the Coordinates (x,y) : " << endl;
		}

		else if (actualArray[i][j] == 'm' or actualArray[i][j] == 'M')
		{
			cout << "Sorry! You lost the game, a mine has exploded at location (" << i << "," << j << ")." << endl;
			break;
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