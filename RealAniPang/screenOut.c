#include <stdio.h>
#include "gameData.h"

void PrintShape(int shapeNum)
{
	if (shapeNum == WSPADE)
		printf("��");
	if (shapeNum == BSPADE)
		printf("��");
	if (shapeNum == WDIA)
		printf("��");
	if (shapeNum == BDIA)
		printf("��");
	if (shapeNum == WHEART)
		printf("��");
	if (shapeNum == BHEART)
		printf("��");
	if (shapeNum == WCLOVER)
		printf("��");
	if (shapeNum == BCLOVER)
		printf("��");
	if (shapeNum == CURS)
		printf("��");
	if (shapeNum == BLANK)
		printf("  ");
}

void PrintScreen(int gameArr[][SIZE_LEN])
{
	int i, j;
	for (i = 0; i < SIZE_LEN; i++)
	{
		for (j = 0; j < SIZE_LEN; j++)
		{
			PrintShape(gameArr[i][j]);
		}
		puts("");
	}
}
