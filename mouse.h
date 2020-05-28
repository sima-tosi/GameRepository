#pragma once

// ƒ}ƒEƒX‚Ì‘€ì
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

// •Ï”
extern bool mouseDown[MOUSE_MAX];
