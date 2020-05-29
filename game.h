#pragma once

#define START_TIME		180		// 背景のみの時間
#define TITLE_TIME		150		// 「問題」を時間
#define QUESTION_TIME	180		// 問題文を読む時間
#define ANSWER_TIME		900		// 解答時間
#define RESULT_TIME		120		// 正解発表時間

#define A1_POS_Y	260			// 選択肢１の縦座標
#define A2_POS_Y	370			// 選択肢２の縦座標
#define A3_POS_Y	480			// 選択肢３の縦座標

// ゲームのシーン管理
enum GAME_SCENE {
	GAME_S,	// 休憩
	GAME_T,	// 準備
	GAME_Q,	// 問題
	GAME_A,	// 解答
	GAME_R,	// 結果
	GAME_C,	// 続行
	GAME_MAX
};

// プロトタイプ宣言
void GameSysInit(void);		// ゲームの初期設定
void GameSceneInit(void);	// ゲームの初期化
int GameMain(void);			// ゲーム循環
void GameMainDraw(void);	// 背景描画
void GameStart(void);		// 休憩シーン
void GameTitle(void);		// 準備シーン
void GameTitleDrow(void);	// 準備描画
void QuestionScene(void);	// 問題シーン
void QuestionDraw(void);	// 問題描画
void AnswerScene(void);		// 解答シーン
void AnswerDraw(void);		// 解答描画
int GameResult(void);		// 結果シーン
void GameResultDraw(void);	// 結果描画
void GameContnue(void);		// ステージアップ
int Score1(void);			// ランク
int Score2(void);			// 忍