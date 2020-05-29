#pragma once

// ��`
#define SCREEN_SIZE_X	700		// ��ʉ��T�C�Y
#define SCREEN_SIZE_Y	600		// ��ʏc�T�C�Y
#define WOOD_SMALL_X	500		// �������؂̉��T�C�Y
#define WOOD_SMALL_Y	100		// �������؂̏c�T�C�Y

#define SMALL_POS_X	100			// �������؂̉����W
#define BIG_WOOD_X	 50			// �傫���؂̉����W
#define START_POS_Y	325			// �X�^�[�g�̏c���W
#define RULE_POS_Y	450			// �V�ѕ������̏c���W
#define BACK_POS_Y	475			// �߂�E���ւ̏c���W

// �V�[���Ǘ�
enum SCENE_ID
{
	SCENE_INIT,		// �����ݒ�
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �v���C��
	SCENE_RESULT,	// ���U���g
	SCENE_RULE,		// ���[��
	SCENE_MAX		
};
// �؂̃T�C�Y
enum SIZE_WOOD {
	BIG,			// �傫��
	SMALL,			// ������
	SIZE_END
};

// �v���g�^�C�v�錾
bool SystemInit(void);	// �����ݒ�
void SceneInit(void);	// ������
void TitleScene(void);	// �^�C�g���V�[��
void TitleDraw(void);	// �^�C�g���`��
void GameScene(void);	// �Q�[���V�[��
void ResultScene(void);	// ���U���g�V�[��
void ResultDraw(void);	// ���U���g�`��
void RuleScene(void);	// ���[���V�[��
void RuleDraw(void);	// ���[���`��

extern int mouseX;			// �}�E�X�w���W
extern int mouseY;			// �}�E�X�x���W
extern bool cutOk;			// �؂��Ă�����