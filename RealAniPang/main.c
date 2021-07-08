#include "common.h"
#include "console.h"
#include "gameData.h"
#include "gameFunc.h"
#include "screenOut.h"
#include "keyProcess.h"

int main(void)
{
	SetConsoleSize(2 * SIZE_LEN, 2 * SIZE_LEN);
	RemoveCursor();
	SetScreen();

	while (1)
	{
		if (ScanScreen() == 0)
			break;
	}

	initCursor();

	while (1)
	{
		if (ProcessKeyInput())
		{
			break;
		}
	}

	system("cls");
	Goto(6, 15);
	printf("GAME OVER");
	ShowScoreWhenGameOver();

	return 0;
}