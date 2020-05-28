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
void GameTitleDrow(void);
void GameMainDraw(void);
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