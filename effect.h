#pragma once

// �t�F�[�h�̐F
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

extern int fade;		// �t�F�[�h�̐F
extern bool fadeIn;		// �t�F�[�h�C�����Ă�H
extern bool fadeOut;	// �t�F�C�h�A�E�g���Ă�H