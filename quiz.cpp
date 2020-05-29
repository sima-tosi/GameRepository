#include "DxLib.h"
#include "quiz.h"
#include "QandA.h"

int quizjyun[Qcnt];		// クイズの順番（バブルで使う）
int quizNo[Qcnt];		// クイズ番号
int quizsuu;			// 今の問題数

// クイズ初期化
void QuizSceneInit(void)
{
	quizsuu = -1;
	for (int a = 0; a < Qcnt; a++)
	{
		quizjyun[a] = GetRand(1000);
		quizNo[a] = a;
	}

	int c;	// 待機場所

	for (int a = Qcnt - 1; a > 1; a--)
	{
		for (int b = 0; b < a; b++)
		{
			if (quizjyun[b] > quizjyun[b + 1])
			{
				c = quizjyun[b];
				quizjyun[b] = quizjyun[b + 1];
				quizjyun[b + 1] = c;
				c = quizNo[b];
				quizNo[b] = quizNo[b + 1];
				quizNo[b + 1] = c;
			}
		}
	}
	
}

// 問題文を送る
char* QuizSend(int level)
{
	quizsuu++;
	switch (level)
	{
	case 0:
		return easy[quizNo[quizsuu]][0];
	case 1:
		return normal[quizNo[quizsuu]][0];
	case 2:
		return hard[quizNo[quizsuu]][0];
	}
}
// 正解を送る
char* AnswerSend(int level)
{
	switch (level)
	{
	case 0:
		return easy[quizNo[quizsuu]][1];
	case 1:
		return normal[quizNo[quizsuu]][1];
	case 2:
		return hard[quizNo[quizsuu]][1];
	}
}
// １つ目の間違いを送る
char* Wrong1Send(int level)
{
	switch (level)
	{
	case 0:
		return easy[quizNo[quizsuu]][2];
	case 1:
		return normal[quizNo[quizsuu]][2];
	case 2:
		return hard[quizNo[quizsuu]][2];
	}
}
// ２つ目の間違いを送る
char* Wrong2Send(int level)
{
	switch (level)
	{
	case 0:
		return easy[quizNo[quizsuu]][3];
	case 1:
		return normal[quizNo[quizsuu]][3];
	case 2:
		return hard[quizNo[quizsuu]][3];
	}
}