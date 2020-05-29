#pragma once

// マウスの操作
enum MOUSE_KEY
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MAX
};

// プロトタイプ宣言
void MouseSysInit(void);		// マウス初期設定
void MouseCheck(void);			// クリック状況
void MousePos(int* x,int* y);	// マウス座標
bool MouseDraw(int x, int y);	// 斬撃描画

// 変数
extern bool mouseDown[MOUSE_MAX];	// 押された？