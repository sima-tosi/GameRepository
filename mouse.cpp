#include "DxLib.h"
#include "mouse.h"

int cutCnt;
int cutImage[9];
bool mouseOld[MOUSE_MAX];
bool mouseNew[MOUSE_MAX];
bool mouseDown[MOUSE_MAX];

void MouseSysInit(void)
{
	for (int mouseID = 0; mouseID <  MOUSE_MAX; mouseID++)
	{
		mouseOld[mouseID] = false;
		mouseNew[mouseID] = false;
		mouseDown[mouseID] = false;
	}
	cutCnt = 0;
	LoadDivGraph("image/ŽaŒ‚,png", 9, 9, 1, 120, 120, cutImage);
}

void MouseCheck(void)
{
	for (int mouseID = 0; mouseID < MOUSE_MAX; mouseID++)
	{
		mouseOld[mouseID] = mouseNew[mouseID];
		mouseNew[mouseID] = false;
	}

	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		mouseNew[MOUSE_LEFT] = true;
	}
	if (GetMouseInput() & MOUSE_INPUT_RIGHT)mouseNew[MOUSE_RIGHT] = true;

	for (int mouseID = 0; mouseID < MOUSE_MAX; mouseID++)
	{
		mouseDown[mouseID] = false;

		if (mouseNew[mouseID] && !mouseOld[mouseID]) mouseDown[mouseID] = true;
	}
}

void MousePos(int* x,int* y)
{
	GetMousePoint(x, y);

	MouseDraw();
}

void MouseDraw(void)
{
	DrawGraph(200, 200, cutImage[4], false);
}