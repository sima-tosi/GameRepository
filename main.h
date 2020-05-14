#pragma once

// ��`
#define SCREEN_SIZE_X 700
#define SCREEN_SIZE_Y 600

// �V�[���Ǘ�
enum SCENE_ID
{
	SCENE_INIT,		// �����ݒ�
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �v���C��
	SCENE_RESULT,	// ���U���g
	SCENE_MAX		
};

// �v���g�^�C�v�錾

bool SystemInit(void);
void SceneInit(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void ResultScene(void);
void ResultDraw(void);