#pragma once

// É}ÉEÉXÇÃëÄçÏ
enum MOUSE_KEY
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MAX
};

void MouseSysInit(void);
void MouseCheck(void);
void MousePos(int* x,int* y);
bool MouseDraw(int x, int y);

// ïœêî
extern bool mouseOld[MOUSE_MAX];
extern bool mouseNew[MOUSE_MAX];
extern bool mouseDown[MOUSE_MAX];
extern int cutMusic;

