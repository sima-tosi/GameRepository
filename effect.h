#pragma once

// フェードの色
enum FADE_COLER
{
	FADE_NULL,	// フェードなし
	FADE_WHITE,	// フェード白
	FADE_BLACK,	// フェード黒
	FADE_MAX
};

// プロトタイプ宣言
void FadeSysInit(void);	// フェード初期化
bool FadeIn(void);		// フェードイン
bool FadeOutB(void);	// フェードアウト黒
bool FadeOutW(void);	// フェードアウト白
void FadeDraw(void);	// フェード描画

extern int fade;		// フェードの色
extern bool fadeIn;		// フェードインしてる？
extern bool fadeOut;	// フェイドアウトしてる？