#pragma once

// フェードの色
enum FADE_COLER
{
	FADE_NULL,
	FADE_WHITE,
	FADE_BLACK,
	FADE_MAX
};

void FadeSysInit(void);
bool FadeIn(void);
bool FadeOutB(void);
bool FadeOutW(void);
void FadeDraw(void);

extern int fade;		// フェードの色
extern bool fadeIn;		// フェードインしてる？
extern bool fadeOut;	// フェイドアウトしてる？