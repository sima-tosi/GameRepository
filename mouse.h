#pragma once

// �}�E�X�̑���
enum MOUSE_KEY
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MAX
};

void MouseSysInit(void);
void MouseCheck(void);
void MousePos(int* x,int* y);
void MouseDraw(void);

// �ϐ�
extern bool mouseOld[MOUSE_MAX];
extern bool mouseNew[MOUSE_MAX];
extern bool mouseDown[MOUSE_MAX];

