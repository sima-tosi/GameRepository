#pragma once

// プロトタイプ宣言
void QuizSceneInit(void);		// クイズ初期化
char* QuizSend(int level);		// 問題文
char* AnswerSend(int level);	// 正解
char* Wrong1Send(int level);	// 一つ目の間違い
char* Wrong2Send(int level);	// 二つ目の間違い