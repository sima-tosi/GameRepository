#include "DxLib.h"
#include "mouse.h"

int cutCnt;					// �؂�A�j��
int cutImage[9];			// �a��
int cutMusic;				// �؂鉹
bool mouseOld[MOUSE_MAX];	// ��
bool mouseNew[MOUSE_MAX];	// ��
bool mouseDown[MOUSE_MAX];	// �����ꂽ�H

// �}�E�X�̏�����
void MouseSysInit(void)
{
	for (int mouseID = 0; mouseID <  MOUSE_MAX; mouseID++)
	{
		mouseOld[mouseID] = false;
		mouseNew[mouseID] = false;
		mouseDown[mouseID] = false;
	}
	cutCnt = 0;
	LoadDivGraph("image/�a��.png", 9, 9, 1, 240, 240, cutImage);
	cutMusic = LoadSoundMem("music/click.mp3");
}

// �N���b�N��
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

// �}�E�X���W
void MousePos(int* x,int* y)
{
	GetMousePoint(x, y);
	cutCnt = 0;
	PlaySoundMem(cutMusic, DX_PLAYTYPE_BACK);
}

// �a���`��
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