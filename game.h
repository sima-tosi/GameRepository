#pragma once

#define START_CHANGE	180		// 背景のみの時間
#define TITLE_CHANGE    150		// 「問題」を時間
#define QUESTION_CHANGE	240		// 問題文を読む時間
#define RESULT_CHANGE   120		// 正解発表時間

// ゲームのシーン管理
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