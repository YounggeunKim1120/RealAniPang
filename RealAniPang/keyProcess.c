#include "common.h"
#include "keyProcess.h"
#include "gameFunc.h"

#define SYS_DELAY 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int ProcessKeyInput(void)
{
	int i;
	int key;

	
	if (_kbhit() != 0)
	{
		key = _getch();

		switch (key)
		{
		case LEFT:
			ShiftLeft();
			break;
		case RIGHT:
			ShiftRight();
			break;
		case UP:
			ShiftUp();
			break;
		case DOWN:
			ShiftDown();
			break;
		case SPACE:
			ClickShape();
			break;
		case 'q':
			if (!ScanAndDetermineGameOver())
				return 1;
		}
	}

	Sleep(SYS_DELAY);

	return 0;
}