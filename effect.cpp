#include "DxLib.h"
#include "effect.h"
#include "main.h"

int fadeCnt;	// �t�F�[�h�̔Z��
int fade;		// �t�F�[�h�̐F
bool fadeIn;	// �t�F�[�h�C�����Ă�H
bool fadeOut;	// �t�F�[�h�A�E�g���Ă�H

void FadeSysInit(void)
{
	fadeCnt = 0;
	fade = FADE_NULL;
	fadeIn = false;
	fadeOut = false;
}
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