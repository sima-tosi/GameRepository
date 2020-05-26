#pragma once

#define START_CHANGE	180		// �w�i�݂̂̎���
#define TITLE_CHANGE    150		// �u���v������
#define QUESTION_CHANGE	180		// ��蕶��ǂގ���
#define RESULT_CHANGE   120		// ���𔭕\����

#define A1_POS_Y	260			// �I�����P�̏c���W
#define A2_POS_Y	370			// �I�����Q�̏c���W
#define A3_POS_Y	480			// �I�����R�̏c���W

// �Q�[���̃V�[���Ǘ�
enum GAME_SCENE {
	GAME_S,
	GAME_T,
	GAME_Q,
	GAME_A,
	GAME_R,
	GAME_C,
	GAME_MAX
};

void GameSysInit(void);
void GameSceneInit(void);
void GameStart(void);
void GameTitle(void);
int GameMain(void);
void QuestionScene(void);
void QuestionDraw(void);
void AnswerScene(void);
void AnswerDraw(void);
int GameResult(void);
void GameResultDraw(void);
int Score1(void);
int Score2(void);
void GameContnue(void);