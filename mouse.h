#pragma once

// �}�E�X�̑���
enum MOUSE_KEY
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MAX
};

// �v���g�^�C�v�錾
void MouseSysInit(void);		// �}�E�X�����ݒ�
void MouseCheck(void);			// �N���b�N��
void MousePos(int* x,int* y);	// �}�E�X���W
bool MouseDraw(int x, int y);	// �a���`��

// �ϐ�
extern bool mouseDown[MOUSE_MAX];	// �����ꂽ�H