#pragma once

#define START_TIME		180		// �w�i�݂̂̎���
#define TITLE_TIME		150		// �u���v������
#define QUESTION_TIME	180		// ��蕶��ǂގ���
#define ANSWER_TIME		900		// �𓚎���
#define RESULT_TIME		120		// ���𔭕\����

#define A1_POS_Y	260			// �I�����P�̏c���W
#define A2_POS_Y	370			// �I�����Q�̏c���W
#define A3_POS_Y	480			// �I�����R�̏c���W

// �Q�[���̃V�[���Ǘ�
enum GAME_SCENE {
	GAME_S,	// �x�e
	GAME_T,	// ����
	GAME_Q,	// ���
	GAME_A,	// ��
	GAME_R,	// ����
	GAME_C,	// ���s
	GAME_MAX
};

// �v���g�^�C�v�錾
void GameSysInit(void);		// �Q�[���̏����ݒ�
void GameSceneInit(void);	// �Q�[���̏�����
int GameMain(void);			// �Q�[���z��
void GameMainDraw(void);	// �w�i�`��
void GameStart(void);		// �x�e�V�[��
void GameTitle(void);		// �����V�[��
void GameTitleDrow(void);	// �����`��
void QuestionScene(void);	// ���V�[��
void QuestionDraw(void);	// ���`��
void AnswerScene(void);		// �𓚃V�[��
void AnswerDraw(void);		// �𓚕`��
int GameResult(void);		// ���ʃV�[��
void GameResultDraw(void);	// ���ʕ`��
void GameContnue(void);		// �X�e�[�W�A�b�v
int Score1(void);			// �����N
int Score2(void);			// �E