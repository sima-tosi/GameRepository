#pragma once

// ��`
#define SCREEN_SIZE_X	700
#define SCREEN_SIZE_Y	600
#define WOOD_SMALL_X	500
#define WOOD_SMALL_Y	100

#define SMALL_POS_X	100
#define BIG_WOOD_X	 50
#define START_POS_Y	325
#define RULE_POS_Y	450
#define BACK_POS_Y	475
#define A1_POS_Y	255
#define A2_POS_Y	370
#define A3_POS_Y	485


// �V�[���Ǘ�
enum SCENE_ID
{
	SCENE_INIT,		// �����ݒ�
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �v���C��
	SCENE_RESULT,	// ���U���g
	SCENE_RULE,
	SCENE_MAX		
};

enum SIZE {
	BIG,
	SMALL,
	SIZE_END
};

struct XY {
	int x;
	int y;
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
void RuleScene(void);
void RuleDraw(void);