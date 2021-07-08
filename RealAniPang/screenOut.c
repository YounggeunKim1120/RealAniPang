#include <stdio.h>
#include "gameData.h"

void PrintShape(int shapeNum)
{
	if (shapeNum == WSPADE)
		printf("¢»");
	if (shapeNum == BSPADE)
		printf("¢¼");
	if (shapeNum == WDIA)
		printf("¡Þ");
	if (shapeNum == BDIA)
		printf("¡ß");
	if (shapeNum == WHEART)
		printf("¢½");
	if (shapeNum == BHEART)
		printf("¢¾");
	if (shapeNum == WCLOVER)
		printf("¢¿");
	if (shapeNum == BCLOVER)
		printf("¢À");
	if (shapeNum == CURS)
		printf("¡Ø");
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
