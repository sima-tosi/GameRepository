#include "DxLib.h"
#include "mouse.h"

int cutCnt;					// Ø‚éƒAƒjƒ
int cutImage[9];			// aŒ‚
int cutMusic;				// Ø‚é‰¹
bool mouseOld[MOUSE_MAX];	// Ì
bool mouseNew[MOUSE_MAX];	// ¡
bool mouseDown[MOUSE_MAX];	// ‰Ÿ‚³‚ê‚½H

void MouseSysInit(void)
{
	for (int mouseID = 0; mouseID <  MOUSE_MAX; mouseID++)
	{
		mouseOld[mouseID] = false;
		mouseNew[mouseID] = false;
		mouseDown[mouseID] = false;
	}
	cutCnt = 0;
	LoadDivGraph("image/aŒ‚”’.png", 9, 9, 1, 120, 120, cutImage);
	cutMusic = LoadSoundMem("music/click.mp3");
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
	cutCnt = 0;
	int t = CheckSoundMem(cutMusic);
	int a = PlaySoundMem(cutMusic, DX_PLAYTYPE_BACK);
	int t2 = CheckSoundMem(cutMusic);
}

void MouseDraw(int x,int y)
{
	if (x > 0 || y > 0)
	{
		if (cutCnt < 9)
		{
			DrawGraph(x - 60, y - 60, cutImage[cutCnt], true);
		}
		cutCnt++;
	}
}