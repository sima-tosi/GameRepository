#include "DxLib.h"
#include "quiz.h"

int quizjyun[70];
int quizNo[70];
int quizsuu;

void QuizSceneInit(void)
{
	quizsuu = 0;
	for (int a = 0; a < 70; a++)
	{
		quizjyun[a] = GetRand(1000);
		quizNo[a] = a;
	}

	int c;	// ‘Ò‹@êŠ

	for (int a = 70 - 1; a > 1; a--)
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

int QuizSend(int level)
{
	// [level][quizNo]
	quizsuu++;
	return quizNo[quizsuu-1];
}
void AnswerSend(int level)
{
	// [level][quizNo]
}
void Wrong1Send(int level)
{
	// [level][quizNo]
}
void Wrong2Send(int level)
{
	// [level][quizNo]
}