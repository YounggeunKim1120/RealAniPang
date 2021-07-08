#include "common.h"
#include "gameFunc.h"
#include "console.h"

int totalScore = 0;

void PlusScore(int plusScoreAmount)
{
	totalScore += plusScoreAmount;
}

void ShowScore(void)
{
	Goto(2, 16);
	printf("���� ���� : %d", totalScore);
}

void ShowScoreWhenGameOver(void)
{
	Goto(6, 17);
	printf("���� ���� : %d", totalScore);
}