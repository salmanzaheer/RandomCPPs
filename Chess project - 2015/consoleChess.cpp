/*
 * Name: Salman Zaheer
 * Roll No: 15L-4120
 * Section: C
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <iomanip>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15
#define DONT_BLINK		0
#define BLINK			1

const int C=8;
const int R=8;
int turn = 0;
int cursorX = 16;
int cursorY = 3;
bool picked = 0;
bool castleP1 = 1;
bool castleP2 = 1;
int deadPos1 = 36;
int deadPos2 = 36;
int save[1024];
int index=0;

void gotorc(char cstr[], int r, int c, int color)
{
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  cout.flush();
  dwCursorPosition.X = c;
  dwCursorPosition.Y = r;
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
  SetConsoleTextAttribute(hConsoleOutput,color);
  cout<<cstr;
  SetConsoleTextAttribute(hConsoleOutput,WHITE);
}
void gotorc(char cstr, int r, int c, int color)
{
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  cout.flush();
  dwCursorPosition.X = c;
  dwCursorPosition.Y = r;
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
  SetConsoleTextAttribute(hConsoleOutput,color);
  cout<<cstr;
  SetConsoleTextAttribute(hConsoleOutput,WHITE);
}
void gotorc(int cstr, int r, int c, int color)
{
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  cout.flush();
  dwCursorPosition.X = c;
  dwCursorPosition.Y = r;
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
  SetConsoleTextAttribute(hConsoleOutput,color);
  cout<<cstr;
  SetConsoleTextAttribute(hConsoleOutput,WHITE);
}

void storePawns(char A[][C],int row, char a)
{
	for (int j = 0; j<C; j++)
	{
		A[row][j]= a;
	}
}
void tempStore1(char A[][C],int row)
{
	A[row][0]='r';
	A[row][1]='h';
	A[row][2]='b';
	A[row][3]='q';
	A[row][4]='k';
	A[row][5]='b';
	A[row][6]='h';
	A[row][7]='r';

}
void tempStore2(char A[][C],int row)
{
	A[row][0]='R';
	A[row][1]='H';
	A[row][2]='B';
	A[row][3]='Q';
	A[row][4]='K';
	A[row][5]='B';
	A[row][6]='H';
	A[row][7]='R';
}
void storeEmptySpace(char A[][C])
{
	for (int i = 2; i<R-2; i++)
	{
		for (int j = 0; j<R; j++)
		{
			A[i][j] = ' ';
		}
	}
}
void initBoard(char A[][C])
{
	tempStore1(A,0);
	storePawns(A,1,'p');
	storePawns(A,6,'P');
	tempStore2(A,7);
	storeEmptySpace(A);
}
void displayBoard(char A[][C])
{
	gotorc(' ',0,0,BLACK);
	gotorc("WASD = movement  L = load  R = restart",0,40,LIGHTGRAY);
	gotorc("ENTER = select  Q = quit and save" ,1,40,LIGHTGRAY);
	cout << "    ";

	for (char i = 65; i < 73; i++)
	{
		gotorc(i,0,(i-64)*4,LIGHTGRAY);
		cout << "   ";
	}
	cout << endl << "  ";
	for (int i = 0; i < 33; i++)
	{
		if (i == 0)
		{
			cout << (char)218;
		}
		else if (i%4 == 0 && i != 32)
		{
			cout << (char)194;
		}
		else if (i == 32)
		{
			cout << (char)191;
		}
		else
		{
			cout << (char)196;
		}
	}
	cout << endl;

	for (int i = 0; i < R; i++)
	{
		gotorc(C-i, (i+1)*2,0,WHITE);
		cout << " " <<(char)179 <<" "; // |
		for (int j = 0; j<C; j++)
		{
			if (A[i][j] >= 65 && A[i][j] <=90)
			{
				gotorc(A[i][j], (i+1)*2, (j+1)*4,WHITE);
				cout << " " << (char)179 <<" "; // |
			}
			else
			{
				gotorc(A[i][j], (i+1)*2, (j+1)*4,DARKGRAY);
				cout << " " << (char)179 <<" "; // |
			}
		}
		cout << endl << "  ";
		for (int k = 0; k <33; k++)
		{
			if(i<C-1)
			{
				if (k == 0)
				{
					cout << (char)195;
				}
				else if (k%4 == 0 && k != 32)
				{
					cout << (char)197;
				}
				else if (k == 32)
				{
					cout << (char)180;
					break;
				}
				else
				{
					cout << (char)196;
				}
			}
		}
		if(i<C-1)
		{
			cout << endl;
		}
	}
	for (int i = 0; i < 33; i++)
	{
		if (i == 0)
		{
			cout << (char)192;
		}
		else if (i%4 == 0 && i != 32)
		{
			cout << (char)193;
		}
		else if (i == 32)
		{
			cout << (char)217;
		}
		else
		{
			cout << (char)196; // -
		}
	}
	if (picked == 0)
	{
		gotorc('>',cursorX,cursorY,LIGHTRED);
		gotorc('<',cursorX,cursorY+2,LIGHTRED);
	}
	else
	{
		gotorc('>',cursorX,cursorY,LIGHTGREEN);
		gotorc('<',cursorX,cursorY+2,LIGHTGREEN);
	}
	if (turn%2 == 0)
	{
		gotorc("PLAYER", 20, 12, WHITE);
		gotorc((turn%2)+1, 20, 19, WHITE);
		gotorc("'s Turn", 20, 20, WHITE);
	}
	else
	{
		gotorc("PLAYER", 20, 12, DARKGRAY);
		gotorc((turn%2)+1, 20, 19, DARKGRAY);
		gotorc("'s Turn", 20, 20, DARKGRAY);
	}
	gotorc(' ', 17 ,0 ,RED);
	cout << endl << endl;
}

bool isValid(char A[][C], int r1, char c1,int r2,char c2);
bool isCheckMateP1(char A[][C]);
bool isCheckMateP2(char A[][C]);

bool outOfBounds(int r1,char c1, int r2, char c2)
{
	if (r1 > C || c1 > C || r2 > C|| c2 >C || r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool ownPiece(char A[][C], int r1, char c1,int r2,char c2)
{
	if (A[r1][c1] == 'K' && A[r2][c2] == 'R' && castleP1 == 1)
	{
		return true;
	}
	if (A[r1][c1] == 'k' && A[r2][c2] == 'r' && castleP2 == 1)
	{
		return true;
	}
	if(A[r1][c1]>=65 && A[r1][c1] <=90 && A[r2][c2]  >=65 && A[r2][c2] <= 90)
	{
		return false;
	}
	if(A[r1][c1]>=97 && A[r1][c1] <=122 && A[r2][c2]  >=97 && A[r2][c2] <= 122)
	{
		return false;
	}
	else
		return true;
}
bool emptySquare(char A[][C], int r1, char c1)
{
	if (A[r1][c1] == ' ')
	{
		return false;
	}
	else
		return true;
}
bool pieceBlock(char A[][C], int r1, char c1,int r2,char c2)
{
	if (A[r1][c1] != 'h' && A[r1][c1] != 'H')
	{
		if (r2 < r1 && c2 < c1)
		{
			for (int i = r1-1, j = c1-1; i > r2, j > c2; i--, j--)
			{
				if (A[i][j] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 < r1 && c2 > c1)
		{
			for (int i = r1-1, j = c1+1; i > r2, j < c2; i--, j++)
			{
				if (A[i][j] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 > r1 && c2 > c1)
		{
			for (int i = r1+1, j = c1+1; i < r2, j < c2; i++, j++)
			{
				if (A[i][j] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 > r1 && c2 < c1)
		{
			for (int i = r1+1, j = c1-1; i < r2, j > c2; i++, j--)
			{
				if (A[i][j] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 < r1 && c2 == c1)
		{
			for (int i = r1-1; i > r2; i--)
			{
				if (A[i][c2] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 == r1 && c2 > c1)
		{
			for (int j = c1+1; j < c2; j++)
			{
				if (A[r2][j] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 > r1 && c2 == c1)
		{
			for (int i = r1+1; i < r2; i++)
			{
				if (A[i][c2] != ' ')
				{
					return false;
				}
			}
		}
		else if (r2 == r1 && c2 < c1)
		{
			for (int j = c1-1; j > c2; j--)
			{
				if (A[r2][j] != ' ')
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool rookValid(int r1, char c1,int r2,char c2)
{
	if ( r2 == r1 || c1 == c2)
	{
		return true;
	}
	else
		return false;
}
bool bishopValid(int r1, char c1,int r2,char c2)
{
	int i=r1,j=c1;
	for (i, j; i < C || j<C; i++,j++)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i < C || j>-1; i++,j--)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i >-1 || j<C; i--,j++)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i > -1 || j>-1 ; i--,j--)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}

	if (i != r2 && j != c2)
	{
		return false;
	}
	return true;
}
bool queenValid(int r1, char c1,int r2,char c2)
{
	if ( r2 == r1 || c1 == c2)
	{
		return true;
	}
	int i=r1,j=c1;
	for (i, j; i < C || j<C; i++,j++)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i < C || j>-1; i++,j--)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i >-1 || j<C; i--,j++)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}
	i=r1,j=c1;
	for (i, j; i > -1 || j>-1 ; i--,j--)
	{
			if (i == r2 && j == c2)
			{
				return true;
			}
	}

	if (i != r2 && j != c2)
	{
		return false;
	}

	if (i != r2 && j != c2)
	{
		return false;
	}
	return true;
}
bool kingValid(char A[][C], int r1, char c1,int r2,char c2)
{
	if (A[r2][c2] == 'R' && castleP1 == 1)
	{
		return true;
	}
	if (A[r2][c2] == 'r' && castleP2 == 1)
	{
		return true;
	}
	if (r2 == r1+1 || r2 == r1-1 || r2== r1)
	{
		if (c2 == c1+1 || c2 == c1-1 || c2 == c1)
		{
			return true;
		}
	}
	return false;
}
bool horseValid(int r1, char c1,int r2,char c2)
{
	if (r2 == r1-2 || r2 == r1+2)
	{
		if (c2 == c1-1 || c2 == c1+1)
		{
			return true;
		}
	}
	else if ( r2 == r1-1 || r2 == r1+1)
	{
		if (c2 == c1-2 || c2 == c1+2)
		{
			return true;
		}
	}
	return false;
}
bool pawnValid(char A[][C], int r1, char c1,int r2,char c2)
{
	if (A[r1][c1] == 'P')
	{
		if (r1 == 6)
		{
			if ( (r2 == r1-1 || r2 == r1-2) && c2 == c1)
			{
				if (A[r2][c2] != ' ')
				{
					return false;
				}
				return true;
			}
		}
		if (r2 == r1-1 && (c2 == c1-1 || c2==c1+1))
		{
			if (A[r2][c2] != ' ')
			{
				return true;
			}
		}
		else
		{
			if ( r2 == r1-1 && c2 == c1)
			{
				if (A[r2][c2] != ' ')
				{
					return false;
				}
				return true;
			}
		}
	}
	if (A[r1][c1] == 'p')
	{
		if (r1 == 1)
		{
			if ( (r2 == r1+1 || r2 == r1+2) && c2 == c1)
			{
				if (A[r2][c2] != ' ')
				{
					return false;
				}
				return true;
			}
		}
		if (r2 == r1+1 && (c2 == c1-1 || c2==c1+1))
		{
			if (A[r2][c2] != ' ')
			{
				return true;
			}
		}
		else
		{
			if ( r2 == r1+1 && c2 == c1)
			{
				if (A[r2][c2] != ' ')
				{
					return false;
				}
				return true;
			}
		}
	}
	return false;
}
void pawnPromotion(char A[][C])
{
	gotorc("INVALID MOVE", 18, 12, BLACK);
	for (int j = 0; j<C; j++)
	{
		if (A[0][j] == 'P')
		{
			A[0][j] = 'Q';
		}
		if (A[7][j] == 'p')
		{
			A[7][j] = 'q';
		}
	}
}


// check where king is and then if any piece's move on that coordinate is valid then check

bool isTurn(char A[][C], int r1,char c1,int r2,char c2)
{
	if (turn%2 == 0 && (A[r1][c1] >= 65 && A[r1][c1] <= 90))
	{
		return true;
	}
	if (turn%2 == 1 && (A[r1][c1] >= 97 && A[r1][c1] <= 122))
	{
		return true;
	}
	if (A[r2][c2] == 'k' || A[r2][c2] == 'K')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isCheckP1(char A[][C])
{
    int i = 0, j = 0;
    for (i; i < C; i++)
	{

		for (j; j < C; j++)
		{
			if (A[i][j] == 'K')
			{
				break;
			}
		}
		if (A[i][j] == 'K')
		{
			break;
		}
	}
	for (int k = 0; k<C; k++)
	{
		for (int l = 0; l < C; l++)
		{
			if (A[k][l] >= 97 && A[k][l] <= 122)
			{
				if (isValid(A,k,l,i,j) == true)
				{
					castleP1 = 0;
					return true;
				}
			}
		}
	}
	return false;
}
bool isCheckP2(char A[][C])
{
    int i = 0, j = 0;
	for (i; i < C; i++)
	{

		for (j=0; j < C; j++)
		{
			if (A[i][j] == 'k')
			{
				break;
			}
		}
		if (A[i][j] == 'k')
		{
			break;
		}
	}
	for (int k = 0; k<C; k++)
	{
		for (int l = 0; l < C; l++)
		{
			if (A[k][l] >= 65 && A[k][l] <= 90)
			{
				if (isValid(A,k,l,i,j) == true)
				{
					castleP2 = 0;
					return true;
				}
			}
		}
	}
	return false;
}

void ifCheck(char A[][C], int r1, char c1, int r2, char c2, char temp1, char temp2)
{
	if (turn%2 == 0 && isCheckP1(A) == true)
	{
		A[r1][c1] = temp1;
		A[r2][c2] = temp2;
		gotorc("INVALID MOVE", 18, 12, LIGHTGRAY);
	}
	else if (turn%2 == 1 && isCheckP1(A) == true)
	{
		turn++;
		gotorc("INVALID MOVE", 18, 12, BLACK);
		if (temp1 == 'k' || temp1 == 'k')
		{
			castleP2 = 0;
		}
		if (isCheckMateP1(A) == true)
		{
			gotorc("P1 CHECKMATE!!",9,40,WHITE);
			gotorc("", 22, 0, LIGHTGRAY);
			exit(0);
		}
		gotorc("P1 CHECK!!",9,40,WHITE);
	}
	else if (turn%2 == 1 && isCheckP2(A) == true)
	{
		A[r1][c1] = temp1;
		A[r2][c2] = temp2;
		gotorc("INVALID MOVE", 18, 12, LIGHTGRAY);

	}
	else if (turn%2 == 0 && isCheckP2(A) == true)
	{
		turn++;
		gotorc("INVALID MOVE", 18, 12, BLACK);
		if (temp1 == 'K' || temp1 == 'R')
		{
			castleP1 = 0;
		}
		if (isCheckMateP2(A) == true)
		{
			gotorc("P2 CHECKMATE!!",9,40,DARKGRAY);
			gotorc("", 22, 0, LIGHTGRAY);
			exit(0);
		}
		gotorc("P2 CHECK!!",9,40,DARKGRAY);
	}
	else
	{
		if (temp1 == 'K' || temp1 == 'R')
		{
			castleP1 = 0;
		}
		if (temp1 == 'k' || temp1 == 'r')
		{
			castleP2 = 0;
		}
		turn++;
		gotorc("P2 CHECK!!",9,40,BLACK);
	}
}

void castling(char A[][C], int r1, char c1, int r2, char c2, char temp1)
{
	gotorc("INVALID MOVE", 18, 12, BLACK);
	if (temp1 == 'K' && r2 == 7 && c2 == 0 && A[r2][c2] == 'R')
	{
		A[7][0] = ' ';
		A[7][2] = 'K';
		A[7][3] = 'R';
		A[7][4] = ' ';
	}
	else if (temp1 == 'K' && r2 == 7 && c2 == 7 && A[r2][c2] == 'R')
	{
		A[7][7] = ' ';
		A[7][6] = 'K';
		A[7][5] = 'R';
		A[7][4] = ' ';
	}
	else if (temp1 == 'k' && r2 == 0 && c2 == 0 && A[r2][c2] == 'r')
	{
		A[0][0] = ' ';
		A[0][2] = 'k';
		A[0][3] = 'r';
		A[0][4] = ' ';
	}
	else if (temp1 == 'k' && r2 == 0 && c2 == 7 && A[r2][c2] == 'r')
	{
		A[0][7] = ' ';
		A[0][6] = 'k';
		A[0][5] = 'r';
		A[0][4] = ' ';
	}
	else
	{
		A[r1][c1] = ' ';
		if (A[r2][c2] >=65 && A[r2][c2] <= 90)
		{
			gotorc(A[r2][c2], 3, deadPos1,WHITE);
			deadPos1 = deadPos1 + 2;
		}
		else if (A[r2][c2] >=97 && A[r2][c2] <= 122)
		{
			gotorc(A[r2][c2], 16, deadPos2,DARKGRAY);
			deadPos2 = deadPos2 +2;
		}
		A[r2][c2] = temp1;
	}
}

void move(char A[][C], int r1,char c1,int r2, char c2)
{
	if (A[r2][c2] != 'K' && A[r2][c2] != 'k')
	{
		char temp1,temp2;
		temp1 = A[r1][c1];
		temp2 = A[r2][c2];
		castling(A,r1,c1,r2,c2,temp1);
		ifCheck(A, r1, c1, r2, c2, temp1,temp2);
		pawnPromotion(A);
		save[index] = r1; save[index +1] = (int)c1; save[index+2] = r2; save[index+3] = (int)c2;
		index = index+4;
	}
}

void saveGame(char name[])
{
	ofstream fout(name);
	fout << index <<endl;
	for (int i = 0; i < index; i++)
	{
		fout << save[i] << endl;
	}
	exit(0);
}

void loadGame(char name[], char A[][C])
{
	int r1,c1,r2,c2,ind;
	char temp;
	initBoard(A);
	displayBoard(A);
	ifstream fin(name);
	fin >> ind;
	for (int i = 0; i < ind/4; i++)
	{
		fin >> r1;
		fin >> c1;
		fin >> r2;
		fin >> c2;

		if(isValid(A,r1,c1,r2,c2) == true)
		{
			move(A,r1,c1,r2,c2);
		}
		displayBoard(A);
		Sleep(1000);
	}
}

void restart(char A[][C])
{
	gotorc("INVALID MOVE", 18, 12, BLACK);
	initBoard(A);
	turn = 0;
	castleP1 = 1;
	castleP2 = 1;
	deadPos1 = 40;
	deadPos2 = 40;
	for (int i = 0; i < 1024; i++)
	{
		save[i] = ' ';
	}
	index=0;
	displayBoard(A);
}
void moveCursor(char A[][C],char ch, int &r1,char &c1,int &r2, char &c2)
{
	if (ch == 'r')
	{
		restart(A);
	}
	if (ch == 'q')
	{
		saveGame("save.txt");
	}
	if (ch == 'l')
	{
		loadGame("save.txt", A);
	}
	if (picked == 0 && ch == 'd')
	{
		if(c1 == 7)
		{
			cursorY = 3;
			c1= 0;
			c2=c1;
		}
		else
		{
			cursorY = cursorY+4;
			c1= c1+1;
			c2=c1;
		}
	}
	if (picked == 0 && ch == 'a')
	{
		if(c1 ==0)
		{
			cursorY = 31;
			c1= 7;
			c2=c1;
		}
		else
		{
			cursorY = cursorY-4;
			c1= c1-1;
			c2=c1;
		}
	}
	if (picked == 0 && ch == 's')
	{
		if(r1 == 7)
		{
			cursorX = 2;
			r1= 0;
			r2=r1;
		}
		else
		{
			cursorX = cursorX+2;
			r1= r1+1;
			r2=r1;
		}
	}
	if (picked == 0 && ch == 'w')
	{
		if(r1 ==0)
		{
			cursorX = 16;
			r1= 7;
			r2=r1;
		}
		else
		{
			cursorX = cursorX-2;
			r1= r1-1;
			r2=r1;
		}
	}
	if (picked == 1 && ch == 'd')
	{
		if(c2 ==7)
		{
			cursorY = 3;
			c2=0;
		}
		else
		{
			cursorY = cursorY+4;
			c2= c2+1;
		}
	}
	if (picked == 1 && ch == 'a')
	{
		if(c2 ==0)
		{
			cursorY = 31;
			c2 = 7;
		}
		else
		{
			cursorY = cursorY-4;
			c2= c2-1;
		}
	}
	if (picked == 1 && ch == 's')
	{
		if(r2 ==7)
		{
			cursorX = 2;
			r2= 0;
		}
		else
		{
			cursorX = cursorX+2;
			r2= r2+1;
		}
	}
	if (picked == 1 && ch == 'w')
	{
		if(r2 ==0)
		{
			cursorX = 16;
			r2=7;
		}
		else
		{
			cursorX = cursorX-2;
			r2= r2-1;
		}
	}
	if (ch == 13 && picked == 1)
	{
		if(isValid(A,r1,c1,r2,c2) == true)
		{
			move(A,r1,c1,r2,c2);
		}
		else if(isValid(A,r1,c1,r2,c2) == false)
		{
			gotorc("INVALID MOVE", 18, 12, LIGHTGRAY);
		}
		picked = 0;
		r1=r2;
		c1=c2;
	}
	else if (ch == 13 && picked == 0)
	{
		picked = 1;
		ch=0;
	}
}

int main()
{
	char arr[R][C];
	char c1=0,c2=0;
	int r1=7,r2=0;
	char ch=0;

	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(45)<<"*********************"<<endl<<endl;
	cout<<setw(45)<<"*       CHESS       *"<<endl<<endl;
	cout<<setw(45)<<"*********************"<<endl<<endl;
	cout<<setw(45)<<"--- Salman Zaheer ---"<<endl;
	cout<<setw(45)<<"--- Section: C    ---"<<endl;
	cout<<setw(45)<<"- Roll no: 15L-4120 -"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(80)<<"Press any key to continue.";
	_getch();
	system("cls");

	initBoard(arr);
	displayBoard(arr);
	while(true)
	{
		ch = getch();
		moveCursor(arr,ch,r1,c1,r2,c2);
		displayBoard(arr);
	}
}

bool isValid(char A[][C], int r1, char c1,int r2,char c2)
{
	if (outOfBounds(r1,c1,r2,c2) == false)
	{
		return false;
	}
	else if (ownPiece(A,r1,c1,r2,c2) == false)
	{
		return false;
	}
	else if (emptySquare(A,r1,c1) == false)
	{
		return false;
	}
	else if (isTurn(A, r1,c1,r2,c2) == false)
	{
		return false;
	}
	else if (pieceBlock(A,r1,c1,r2,c2) == false)
	{
		return false;
	}
	if (A[r1][c1] == 'r' || A[r1][c1] == 'R')
	{
		if (rookValid(r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	if (A[r1][c1] == 'b' || A[r1][c1] == 'B')
	{
		if (bishopValid(r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	if (A[r1][c1] == 'q' || A[r1][c1] == 'Q')
	{
		if (queenValid(r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	if (A[r1][c1] == 'k' || A[r1][c1] == 'K')
	{
		//if opponent king is around it
		if (kingValid(A,r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	if (A[r1][c1] == 'h' || A[r1][c1] == 'H')
	{
		if (horseValid(r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	if (A[r1][c1] == 'p' || A[r1][c1] == 'P')
	{
		if (pawnValid(A,r1,c1,r2,c2) == false)
		{
			return false;
		}
	}
	return true;
}

bool isCheckMateP1(char A[][C])
{
	for (int i = 0; i<C; i++)
	{
		for (int j = 0; j<C; j++)
		{
			if ( A[i][j] >=65 && A[i][j] <= 90)
			{
				for (int k = 0; k<C; k++)
				{
					for (int l = 0; l<C; l++)
					{
						if(isValid(A,i,j,k,l) == true)
						{
							char temp1,temp2;
							temp1 = A[i][j];
							A[i][j] = ' ';
							temp2 = A[k][l];
							A[k][l] = temp1;
							if (isCheckP1(A) == false)
							{
								A[i][j] = temp1;
								A[k][l] = temp2;
								return false;
							}
							else
							{
								A[i][j] = temp1;
								A[k][l] = temp2;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool isCheckMateP2(char A[][C])
{
	for (int i = 0; i<C; i++)
	{
		for (int j = 0; j<C; j++)
		{
			if ( A[i][j] >=97 && A[i][j] <= 122)
			{
				for (int k = 0; k<C; k++)
				{
					for (int l = 0; l<C; l++)
					{
						if(isValid(A,i,j,k,l) == true)
						{
							char temp1,temp2;
							temp1 = A[i][j];
							A[i][j] = ' ';
							temp2 = A[k][l];
							A[k][l] = temp1;
							if (isCheckP2(A) == false)
							{
								A[i][j] = temp1;
								A[k][l] = temp2;
								return false;
							}
							else
							{
								A[i][j] = temp1;
								A[k][l] = temp2;
							}
						}
					}
				}
			}
		}
	}
	return true;
}