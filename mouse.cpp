#include "DxLib.h"
#include "mouse.h"

int cutCnt;					// 切るアニメ
int cutImage[9];			// 斬撃
int cutMusic;				// 切る音
bool mouseOld[MOUSE_MAX];	// 昔
bool mouseNew[MOUSE_MAX];	// 今
bool mouseDown[MOUSE_MAX];	// 押された？

// マウスの初期化
void MouseSysInit(void)
{
	for (int mouseID = 0; mouseID <  MOUSE_MAX; mouseID++)
	{
		mouseOld[mouseID] = false;
		mouseNew[mouseID] = false;
		mouseDown[mouseID] = false;
	}
	cutCnt = 0;
	LoadDivGraph("image/斬撃.png", 9, 9, 1, 240, 240, cutImage);
	cutMusic = LoadSoundMem("music/click.mp3");
}

// クリック状況
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

// マウス座標
void MousePos(int* x,int* y)
{
	GetMousePoint(x, y);
	cutCnt = 0;
	PlaySoundMem(cutMusic, DX_PLAYTYPE_BACK);
}

// 斬撃描画
bool MouseDraw(int x,int y)
{
	if (x > 0 || y > 0)
	{
		if (cutCnt < 27)
		{
			DrawGraph(x - 120, y - 120, cutImage[cutCnt / 2], true);
			cutCnt++;
			return false;
		}
	}
	return true;
}