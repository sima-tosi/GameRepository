#pragma once

#define TITLE_CHANGE    120
#define QUESTION_CHANGE	240
#define RESULT_CHANGE   180

enum GAME_SCENE {
	GAME_T,
	GAME_Q,
	GAME_A,
	GAME_R,
	GAME_C,
	GAME_MAX
};

void GameSysInit(void);
void GameSceneInit(void);
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