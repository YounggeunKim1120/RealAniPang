#include "common.h"
#include "gameData.h"
#include "console.h"
#include "screenOut.h"
#include "deleteStruct.h"
#include "scoreManage.h"

#define BLANK_TIME 300
#define DELETE_SHAPE_ARR_IDX 40

int shapeArr[SIZE_LEN][SIZE_LEN];

int curCursX = 0;
int curCursY = 0;
int shape1 = 0;
int shape2 = 0;
int clickCursorX;
int clickCursorY;
int switchNum = 0;

deleteShape DSA[DELETE_SHAPE_ARR_IDX];

void SetScreen(void)
{
	int i, j;
	srand(time(NULL));
	for (i = 0; i < SIZE_LEN; i++)
	{
		for (j = 0; j < SIZE_LEN; j++)
		{
			shapeArr[i][j] = rand() % 8 + 1;
		}
	}
	PrintScreen(shapeArr);
}

void SwapShape(int curs1X, int curs1Y, int curs2X, int curs2Y)
{
	int temp;

	Goto(2 * curs1X, curs1Y);
	PrintShape(shapeArr[curs2Y][curs2X]);

	Goto(2 * curs2X, curs2Y);
	PrintShape(shapeArr[curs1Y][curs1X]);

	temp = shapeArr[curs1Y][curs1X];
	shapeArr[curs1Y][curs1X] = shapeArr[curs2Y][curs2X];
	shapeArr[curs2Y][curs2X] = temp;
}

void initCursor(void)
{
	Goto(0, 0);
}

void ShiftLeft(void)
{
	if (curCursX > 0)
	{
		Goto(2 * curCursX, curCursY);
		PrintShape(shapeArr[curCursY][curCursX]);
		curCursX--;
		Goto(2 * curCursX, curCursY);
		PrintShape(CURS);
	}
}

void ShiftRight(void)
{
	if (curCursX < 11)
	{
		Goto(2 * curCursX, curCursY);
		PrintShape(shapeArr[curCursY][curCursX]);
		curCursX++;
		Goto(2 * curCursX, curCursY);
		PrintShape(CURS);
	}
}

void ShiftUp(void)
{
	if (curCursY > 0)
	{
		Goto(2 * curCursX, curCursY);
		PrintShape(shapeArr[curCursY][curCursX]);
		curCursY--;
		Goto(2 * curCursX, curCursY);
		PrintShape(CURS);
	}
}

void ShiftDown(void)
{
	if (curCursY < 11)
	{
		Goto(2 * curCursX, curCursY);
		PrintShape(shapeArr[curCursY][curCursX]);
		curCursY++;
		Goto(2 * curCursX, curCursY);
		PrintShape(CURS);
	}
}

void DeleteAndFillShape(void)
{
	int i, j;
	int n = 0;
	int UpBlankY;
	int DownBlankY;
	int term = 0;

	srand(time(NULL));

	while (DSA[n].x != -1)
	{
		if (DSA[n].nextX > 0)
		{
			for (i = 0; i < DSA[n].nextX; i++)
			{
				shapeArr[DSA[n].y][DSA[n].x + i] = BLANK;
				Goto(2 * (DSA[n].x + i), DSA[n].y);
				PrintShape(BLANK);
			}
			PlusScore(DSA[n].nextX);
			ShowScore();
		}
		else if (DSA[n].nextY > 0) 
		{
			for (i = 0; i < DSA[n].nextY; i++)
			{
				shapeArr[DSA[n].y + i][DSA[n].x] = BLANK;
				Goto(2 * DSA[n].x, DSA[n].y + i);
				PrintShape(BLANK);
			}
			PlusScore(DSA[n].nextY);
			ShowScore();
		}
		n++;
	}

	Sleep(BLANK_TIME);

	n = 0;
	while (DSA[n].x != -1)
	{
		if (DSA[n].nextX > 0)
		{
			if (DSA[n].y > 0)
			{
				for (i = DSA[n].x; i < DSA[n].x + DSA[n].nextX; i++)
				{
					for (j = DSA[n].y; j > 0; j--)
					{
						shapeArr[j][i] = shapeArr[j - 1][i];
						Goto(2 * i, j);
						PrintShape(shapeArr[j][i]);
					}
				}
			}
			for (i = DSA[n].x; i < DSA[n].x + DSA[n].nextX; i++)
			{
				shapeArr[0][i] = rand() % 8 + 1;
				Goto(2 * i, 0);
				PrintShape(shapeArr[0][i]);
			}
		}
		else if (DSA[n].nextY > 0)
		{
			for (i = 0; i < 12; i++)
			{
				if (i == 0 && (shapeArr[i][DSA[n].x] == BLANK))
				{
					if (n > 0 && DSA[n - 1].nextY > 0 && DSA[n].x == DSA[n - 1].x)
					{
						++i;
						break;
					}
					else
					{
						UpBlankY = 0;
						break;
					}
				}
				if (shapeArr[i][DSA[n].x] != BLANK && shapeArr[i + 1][DSA[n].x] == BLANK)
				{
					if (n > 0 && DSA[n - 1].nextY > 0 && DSA[n].x == DSA[n - 1].x)
					{
						++i;
						break;
					}
					else
					{
						UpBlankY = i + 1;
						break;
					}
				}
			}
			for (i = 0; i < 12; i++)
			{
				if (i == 11 && shapeArr[i][DSA[n].x] == BLANK)
				{
					DownBlankY = 11;
					break;
				}
				else if (shapeArr[i][DSA[n].x] == BLANK && shapeArr[i + 1][DSA[n].x] != BLANK)
				{
					if (n > 0 && DSA[n - 1].nextY > 0 && DSA[n].x == DSA[n - 1].x)
					{
						++i;
						break;
					}
					else
					{
						DownBlankY = i;
						break;
					}
				}
			}

			term = DownBlankY - UpBlankY + 1;

			for (i = UpBlankY - 1; i >= 0; i--)
			{
				shapeArr[i + term][DSA[n].x] = shapeArr[i][DSA[n].x];
				Goto(2 * DSA[n].x, i + term);
				PrintShape(shapeArr[i][DSA[n].x]);
			}
			for (i = 0; i < term; i++)
			{
				shapeArr[i][DSA[n].x] = rand() % 8 + 1;
				Goto(2 * DSA[n].x, i);
				PrintShape(shapeArr[i][DSA[n].x]);
			}
		}
		n++;
	}
}

int ScanScreen(void)
{
	int i, j;
	int n = 0;
	int whetherDelete = 0;

	for (i = 0; i < 15; i++)
	{
		DSA[i].x = -1;
		DSA[i].y = -1;
		DSA[i].nextX = 0;
		DSA[i].nextY = 0;
	}

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (shapeArr[i][j] == shapeArr[i][j + 1] && shapeArr[i][j + 1] == shapeArr[i][j + 2])
			{
				if (j < 9 && shapeArr[i][j + 2] == shapeArr[i][j + 3])
				{
					if (j < 8 && shapeArr[i][j + 3] == shapeArr[i][j + 4])
						DSA[n].nextX = 5;
					else 
						DSA[n].nextX = 4;
				}
				else
					DSA[n].nextX = 3;

				DSA[n].x = j;
				DSA[n].y = i;

				j += DSA[n].nextX - 1;
				whetherDelete = 1;
				n++;
			}		
		}
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (shapeArr[j][i] == shapeArr[j + 1][i] && shapeArr[j + 1][i] == shapeArr[j + 2][i])
			{
				if (j < 9 && shapeArr[j + 2][i] == shapeArr[j + 3][i])
				{
					if (j < 8 && shapeArr[j + 3][i] == shapeArr[j + 4][i])
						DSA[n].nextY = 5;
					else
						DSA[n].nextY = 4;
				}
				else
					DSA[n].nextY = 3;

				DSA[n].x = i;
				DSA[n].y = j;

				j += DSA[n].nextY - 1;
				whetherDelete = 1;
				n++;
			}
		}
	}



	if (whetherDelete)
	{
		DeleteAndFillShape();
		return 1;
	}
	return 0; 
}


void ClickShape(void)
{
	if (switchNum == 0)
	{
		clickCursorX = curCursX;
		clickCursorY = curCursY;
		Goto(2 * curCursX, curCursY);
		PrintShape(shapeArr[curCursY][curCursX]);
		switchNum = 1;
	}
	if (switchNum == 1)
	{
		if ((abs(clickCursorX - curCursX) == 1 && (clickCursorY == curCursY)) || (abs(clickCursorY - curCursY) == 1 && (clickCursorX == curCursX)))
		{
			SwapShape(clickCursorX, clickCursorY, curCursX, curCursY);
			Sleep(BLANK_TIME);
			if(!ScanScreen())
				SwapShape(clickCursorX, clickCursorY, curCursX, curCursY);
			while (ScanScreen());
			switchNum = 0;
		}
		else
		{
			clickCursorX = curCursX;
			clickCursorY = curCursY;
			Goto(2 * curCursX, curCursY);
			PrintShape(shapeArr[curCursY][curCursX]);
			switchNum = 1; 
		}
	}
}

int ScanAndDetermineGameOver(void)
{
	int i, j, k, l;
	int tempArr[SIZE_LEN][SIZE_LEN];
	int temp;

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 10; j++)
		{
			tempArr[i][j] = shapeArr[i][j];
		}
	}

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			temp = tempArr[i][j];
			tempArr[i][j] = tempArr[i][j + 1];
			tempArr[i][j + 1] = temp;

			if (j >= 2)
			{
				if (tempArr[i][j - 2] == tempArr[i][j - 1] && tempArr[i][j - 1] == tempArr[i][j])
					return 1;
			}

			if (i >= 2)
			{
				if (tempArr[i - 2][j] == tempArr[i - 1][j] && tempArr[i - 1][j] == tempArr[i][j])
					return 1;
				if (j < 11)
				{
					if (tempArr[i - 2][j + 1] == tempArr[i - 1][j + 1] && tempArr[i - 1][j + 1] == tempArr[i][j + 1])
						return 1;
				}
			}

			if (i >= 1 && i <= 10)
			{
				if (tempArr[i - 1][j] == tempArr[i][j] && tempArr[i][j] == tempArr[i + 1][j])
					return 1;
				if (j < 11)
				{
					if (tempArr[i - 1][j + 1] == tempArr[i][j + 1] && tempArr[i][j + 1] == tempArr[i + 1][j + 1])
						return 1;
				}
			}

			if (i <= 9)
			{
				if (tempArr[i + 2][j] == tempArr[i + 1][j] && tempArr[i + 1][j] == tempArr[i][j])
					return 1;
				if (j < 11)
				{
					if (tempArr[i + 2][j + 1] == tempArr[i + 1][j + 1] && tempArr[i + 1][j + 1] == tempArr[i][j + 1])
						return 1;
				}
			}

			if (j <= 8)
			{
				if (tempArr[i][j + 3] == tempArr[i][j + 2] && tempArr[i][j + 2] == tempArr[i][j + 1])
					return 1;
			}
		}
	}
	return 0;
}