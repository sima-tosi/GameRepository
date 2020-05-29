#include "DxLib.h"
#include "effect.h"
#include "main.h"

int fadeCnt;	// フェードの濃さ
int fade;		// フェードの色
bool fadeIn;	// フェードインしてる？
bool fadeOut;	// フェードアウトしてる？

// フェード初期設定
void FadeSysInit(void)
{
	fadeCnt = 0;
	fade = FADE_NULL;
	fadeIn = false;
	fadeOut = false;
}

// フェードイン
bool FadeIn(void)
{
	fadeCnt -= 4;
	if (fadeCnt <= 0)
	{
		fadeIn = false;
		fadeCnt = 0;
		fade = FADE_NULL;
		return true;
	}
	return false;
}

// 黒フェードアウト
bool FadeOutB(void)
{
	fadeCnt += 4;

	if (fadeCnt >= 255)
	{
		fadeCnt = 255;
		fadeIn = true;
		fadeOut = false;
		return true;
	}
	return false;
}
// 白フェードアウト
bool FadeOutW(void)
{
	fadeCnt += 4;
	if (fadeCnt >= 255)
	{
		fadeCnt = 255;
		fadeIn = true;
		fadeOut = false;
		return true;
	}
	return false;
}

// フェードの描画
void FadeDraw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt);
	if (fade == FADE_WHITE)
	{
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
	}
	 else if (fade == FADE_BLACK)
	{
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}