#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define _WIN32_WINNT 0x0500

#include <windows.h>

using namespace std;


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

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int R = 40;
const int C = 80;
int pi = 2, pj = (C/2)-1;
int level = 1;
int score = 0;
int missCount = 0;
int initialSpeed = 40;
int speed = initialSpeed;
int rectangleSize = 25;
int newRectangleSize=rectangleSize;
int direction = 1;
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
void gotorc(int a, int r, int c, int color)
{
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  cout.flush();
  dwCursorPosition.X = c;
  dwCursorPosition.Y = r;
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
  SetConsoleTextAttribute(hConsoleOutput,color);
  cout<<a;
  SetConsoleTextAttribute(hConsoleOutput,WHITE);
}

void displayAndSave(char A[][C], char ch, int i, int j, int color)
{
	A[i][j] = ch;
	gotorc(ch,i, j, color);
}

void displayBoard(char A[][C])
{
	for(int j = 1; j< C-1;j++)
	{
		displayAndSave(A, 0, R-2, j, BLACK);
	}
	for(int i=0;i<R;i++)
	{
		if (i == 0)
		{
			displayAndSave(A,'|',i,0,LIGHTBLUE);
		}
		else
		{
			displayAndSave(A,'|',i,0,LIGHTBLUE);
		}
	}
	for(int i=0;i<R;i++)
	{
		if (i == 0)
		{
			displayAndSave(A,'|',i,C-1,LIGHTBLUE);
		}
		else
		{
			displayAndSave(A,'|',i,C-1,LIGHTBLUE);
		}
	}
	for(int i=0;i<C;i++)
	{
		displayAndSave(A,'-',1,i,LIGHTBLUE);
	}
	for(int i=0;i<C;i++)
	{
		displayAndSave(A,196,R-1,i,LIGHTBLUE);
	}
	gotorc("SCORE:",0,2,LIGHTBLUE);
	gotorc(score,0,8,LIGHTBLUE);
	gotorc("H:high scores",0,C-50,LIGHTBLUE);
	gotorc("Q:Quit",0,C-20,LIGHTBLUE);
	gotorc("L",0,C-3,LIGHTBLUE);
	gotorc(level,0,C-2,LIGHTBLUE);
	gotorc(missCount,0,23,LIGHTBLUE);
	gotorc("/3",0,24,LIGHTBLUE);
}
void displayRectangle(char A[][C], int size)
{
	int j = 0;
	for(int i = ((C/2)-1)-(size/2); j<size; i++,j++)
	{
		displayAndSave(A,'-',R-2,i,LIGHTBLUE);
	}
}
void shrinkRectangle(char A[][C])
{
	for(int i = 1; i < C-1;i++)
	{
		if(A[R-2][i] == '-')
		{
			displayAndSave(A,0,R-2,i,BLACK);
			break;
		}
	}
	for(int i = C-1; i > 0;i--)
	{
		if(A[R-2][i] == '-')
		{
			displayAndSave(A,0,R-2,i,BLACK);
			break;
		}
	}
}
void createFile(char saveFile[])
{
	ifstream fin(saveFile);
	if(!fin)
	{
		ofstream fout(saveFile);
		fout<< 0 << " " << 0 << "" << 0;
	}


}
void writeScores(char saveFile[])
{
	int highScore[4];
	ifstream fin(saveFile);
	fin >> highScore[0];
	fin >> highScore[1];
	fin >> highScore[2];
	if(score > highScore[2] && score <= highScore[1])
	{
		ofstream fout(saveFile);
		fout << highScore[0] << " " << highScore[1] << " " << score;
	}
	if(score > highScore[1] && score <= highScore[0])
	{
		highScore[2] = highScore[1];
		highScore[1] = score;
		ofstream fout(saveFile);
		fout << highScore[0] << " " << highScore[1] << " " << highScore[2];
	}
	if(score > highScore[0])
	{
		highScore[2] = highScore[1];
		highScore[1] = highScore[0];
		highScore[0] = score;
		ofstream fout(saveFile);
		fout << highScore[0] << " " << highScore[1] << " " << highScore[2];
	}
}
void ifThreeMisses(char A[][C])
{
	writeScores("save.txt");
	score=0;
	missCount=0;
	level = 1;
	gotorc(missCount,0,23,LIGHTGRAY);
	gotorc("SCORE:",0,2,LIGHTBLUE);
	gotorc(score,0,8,LIGHTBLUE);
	gotorc("    ",0,8,BLACK);
	newRectangleSize=rectangleSize;
	displayBoard(A);
	displayRectangle(A,rectangleSize);
	direction = 1;
	gotorc("Game Over",R/2,C/3,WHITE);
	Sleep(3000);
	gotorc("Game Over",R/2,C/3,BLACK);
}
void showHighScores(char A[][C])
{
	int fileScore;
	ifstream fin("save.txt");
	if (fin.fail())
	{
		gotorc("Save file not found",2,C-25,WHITE);
	}
	else
	{
		for (int i = 2; i<5; i++)
		{

			fin >> fileScore;
			gotorc(i-1,i,C-7,LIGHTBLUE);
			gotorc('.',i,C-6,LIGHTBLUE);
			gotorc(fileScore,i,C-4,LIGHTBLUE);
		}
		Sleep(1000);
		for (int i = 2; i<5; i++)
		{
			fin >> fileScore;
			gotorc(i-1,i,C-7,BLACK);
			gotorc('.',i,C-6,BLACK);
			gotorc(fileScore,i,C-4,BLACK);
		}
	}
	fin.close();
}

void moveBall(char A[][C], int &i, int &j, int &direction, int &pi, int &pj)
{
	while(!kbhit())
	{
		if (score == 0)
			{
				speed = initialSpeed;
			}
		if(score%20 == 0 && speed >=5 && score != 0)
		{
				speed = speed -3;
				score = score+2;
				level++;
				gotorc(level,0,C-2,WHITE);
				if (newRectangleSize >2 && speed > 7)
				{
					Sleep(1000);
					shrinkRectangle(A);
					newRectangleSize = newRectangleSize-2;
				}
				else
				{
					Sleep(1000);
				}

		}
		if(A[R-2][j] == 'X')
		{
			displayAndSave(A,0,R-2,j,BLACK);
		}
		if(A[R-3][j] == 'O' && A[R-2][j] != '-' && direction == 1)
		{
			displayAndSave(A,0,R-4,j,BLACK);
			displayAndSave(A,0,R-3,j,BLACK);
			displayBoard(A);
			displayRectangle(A,newRectangleSize);
			missCount++;
			gotorc(missCount,0,23,LIGHTBLUE);
			if(missCount >2)
			{
				ifThreeMisses(A);
			}
			i=2;
			j = (C/2)-1;
			direction = 1;
			if (direction == 5)
			{
				direction = 1;
			}
			break;
		}
		if(A[R-3][j-1] == 'O' && A[R-2][j-1] != '-' && direction == 3)
		{
			displayAndSave(A,0,R-3,j-1,BLACK);
			if(A[R-3][j-1] == 0 && A[R-2][j]== '-')
			{
				Sleep(1000);
				displayAndSave(A,'-',R-2,j,LIGHTBLUE);
			}
			else
			{
			}
			displayBoard(A);
			displayRectangle(A,newRectangleSize);
			missCount++;
			gotorc(missCount,0,23,LIGHTBLUE);
			if(missCount >2)
			{
				ifThreeMisses(A);
			}
			j = (C/2)-1;
			i=2;
			direction = 1;
			if (direction == 5)
			{
				direction = 1;
			}
			break;
		}
		if(A[R-3][j+1] == 'O' && A[R-2][j+1] != '-' && direction == 4)
		{
			displayAndSave(A,0,R-3,j+1,BLACK);
			if(A[R-3][j+1] == 0 && A[R-2][j]== '-')
			{
				Sleep(1000);
				displayAndSave(A,'-',R-2,j,LIGHTBLUE);
			}
			else
			{
			}
			displayBoard(A);
			displayRectangle(A,newRectangleSize);
			missCount++;
			gotorc(missCount,0,23,LIGHTBLUE);
			if(missCount >2)
			{
				ifThreeMisses(A);
			}
			j = (C/2)-1;
			direction = 1;
			if (direction == 5)
			{
				direction = 1;
			}
			i=2;
			break;
		}
		if(direction == 1)
		{
			for(i; i <R-2 && !kbhit(); i++)
			{
				Sleep(speed);
				if(i>2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
				}
				displayAndSave(A,'O',i,j,LIGHTBLUE);
				pi = i;
				pj = j;
			}
			if (A[i][j] == '-')
			{
				direction = rand() % 3 + 5;
				score = score+2;
				gotorc(score,0,8,LIGHTBLUE);
				if(direction == 7)
				{
					direction = 2;
				}
				else if (direction == 5 || direction == 6)
				{
					i--;
				}
			}
		}
		else if(direction == 2)
		{
			for(i-1; i-1>2 && !kbhit(); i--)
			{
				Sleep(speed);
				displayAndSave(A,0,pi,pj,BLACK);
				displayAndSave(A,'O',i-2,j,LIGHTBLUE);
				pi=i-2;
				pj=j;
			}
			if (A[i-2][j] == '-')
			{
				direction = 1;
			}
		}
		if(direction == 3)
		{
			for(i,j; i <R-2 && j <C-1 && !kbhit(); i++,j++)
			{
				Sleep(speed);
				if (j==C-2)
				{
					direction = 4;
					break;
				}

				if(i>2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
				}
				displayAndSave(A,'O',i,j,LIGHTBLUE);
				pi = i;
				pj = j;
			}
			if (i == R-2 && A[R-2][j-1] == '-')
			{
				direction = rand() % 3 + 5;
				score = score+2;
				gotorc(score,0,8,LIGHTBLUE);
				if (direction == 7)
				{
					direction = 1;
					j--;
				}
				else if(direction == 5)
				{
					i = i-2;
				}
				else if (direction == 6)
				{
					j--;
					i--;
				}
			}
		}
		if(direction == 4)
		{
			for(i,j; i <R-2 && j >1 && !kbhit(); i++,j--)
			{
				Sleep(speed);
				if (j==2)
				{
					direction = 3;
					break;
				}
				if(i>2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
				}
				displayAndSave(A,'O',i,j,LIGHTBLUE);
				pi = i;
				pj = j;
			}
			if (i == R-2 && A[R-2][j+1] == '-')
			{
				direction = rand() % 3 + 5;
				score = score+2;
				gotorc(score,0,8,LIGHTBLUE);
				if (direction == 7)
				{
					direction = 1;
					j++;
				}
				else if(direction == 5)
				{
					i--;
					j++;
				}
				else if (direction == 6)
				{
					j++;
					i--;
				}
			}
		}
		if(direction == 5)
		{
			for(i,j; i > 1 && j <C-1 && !kbhit(); i--,j++)
			{
				Sleep(speed);
				if (j==C-2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
					displayAndSave(A,'O',i,j,LIGHTBLUE);
					displayAndSave(A,0,i,j,BLACK);
					j--;
					direction = 6;
					break;
				}
				if(i>1)
				{
					displayAndSave(A,0,pi,pj,BLACK);
				}
				displayAndSave(A,'O',i,j,LIGHTBLUE);
				pi = i;
				pj = j;
				if(i==2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
					direction = 3;
					break;
				}
			}
		}
		if(direction == 6)
		{
			for(i,j; i > 1 && j >1 && !kbhit(); i--,j--)
			{
				Sleep(speed);
				if (j==2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
					displayAndSave(A,'O',i,j,LIGHTBLUE);
					displayAndSave(A,0,i,j,BLACK);
					j--;
					direction = 5;
					break;
				}
				if(i>1)
				{
					displayAndSave(A,0,pi,pj,BLACK);
				}
				displayAndSave(A,'O',i,j,LIGHTBLUE);
				pi = i;
				pj = j;
				if(i==2)
				{
					displayAndSave(A,0,pi,pj,BLACK);
					direction = 4;
					break;
				}
			}
		}
	}

}

void moveRectangle(char A[][C], int direction)
{
	for(int i = 0; i < C-1;i++)
	{
		if(A[R-2][i] == '-')
		{
			if (direction == 1)
			{
				if(A[R-2][C-2] == '-')
				{
					break;
				}
				displayAndSave(A,0,R-2,i,BLACK);
				i++;
				for(i; i <C-1;i++)
				{
					if (A[R-2][i] != '-')
					{
						displayAndSave(A,'-',R-2,i,LIGHTBLUE);
						break;
					}

				}
			}
			if (direction == 2)
			{
				if(A[R-2][1] == '-')
				{
					break;
				}
				displayAndSave(A,'-',R-2,i-1,LIGHTBLUE);
				for(i; i <C-1;i++)
				{
					if (A[R-2][i+1] != '-')
					{
						displayAndSave(A,0,R-2,i,BLACK);
						break;
					}
				}
			}
			break;
		}
	}
}


int main()
{

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, true);

	char board[R][C];
	char ch;
	int ballPosX = (C/2)-1;
	int ballPosY = 2;
	displayBoard(board);
	displayRectangle(board,rectangleSize);
	createFile("save.txt");
	while(true)
	{
		moveBall(board,ballPosY,ballPosX,direction,pi,pj);
		ch = getch();
		if (ch == KEY_RIGHT)
		{
			moveRectangle(board, 1);
		}
		else if (ch == KEY_LEFT)
		{
			moveRectangle(board, 2);
		}
		else if (ch == 'q' || ch == 'Q')
		{
			cout << endl;
			writeScores("save.txt");
			return 0;
		}
		else if (ch == 'H' || ch == 'h')
		{
			showHighScores(board);
		}
	}
}
