#pragma once

// �t�F�[�h�̐F
enum FADE_COLER
{
	FADE_NULL,	// �t�F�[�h�Ȃ�
	FADE_WHITE,	// �t�F�[�h��
	FADE_BLACK,	// �t�F�[�h��
	FADE_MAX
};

// �v���g�^�C�v�錾
void FadeSysInit(void);	// �t�F�[�h������
bool FadeIn(void);		// �t�F�[�h�C��
bool FadeOutB(void);	// �t�F�[�h�A�E�g��
bool FadeOutW(void);	// �t�F�[�h�A�E�g��
void FadeDraw(void);	// �t�F�[�h�`��

extern int fade;		// �t�F�[�h�̐F
extern bool fadeIn;		// �t�F�[�h�C�����Ă�H
extern bool fadeOut;	// �t�F�C�h�A�E�g���Ă�H