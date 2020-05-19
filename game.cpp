#include "DxLib.h"
#include "game.h"
#include "main.h"
#include "mouse.h"
#include "effect.h"
#include "quiz.h"

int gamescene;

int cnt;						// �w�i�p�J�E���g
int oCnt;						// ����
int stage;						// �X�e�[�W��
int life;						// �c�@
int time;						// ��������
int changeTime;					// �V�[���̕ύX�����鎞��
int A[3];						// �I��ԍ�
int QWide;
int AWide[3];
int soundNew;
int soundOld;
bool cutA[3];					// �؂��Ă邩�H
bool check[3];					// ���肷��H
char* quiz[3];		// �I����
char* Q;			// ��蕶

int gameFont;		// ���C�t�E���ԃt�H���g
int quizFont;		// ��蕶�E�I�����t�H���g
int answerFont;

int oMusic;			// ������
int xMusic;			// �s������

int lifeImage;		// �c�@�̊G
int timeImage;		// ���Ԃ̊G
int toiImage;		// ���
int backImage[3][2];// �w�i[�X�e�[�W][�A�j���[�V����]
int woodImage[SIZE_END];	// ��[��E��]

void GameSysInit(void)
{
	// ���y
	oMusic = LoadSoundMem("music/O.mp3");
	xMusic = LoadSoundMem("music/X.mp3");

	// �C���X�g�̏�����
	woodImage[0] = LoadGraph("image/���.png");
	woodImage[1] = LoadGraph("image/�I����.png");
	lifeImage = LoadGraph("image/life.png");
	timeImage = LoadGraph("image/time.png");
	toiImage = LoadGraph("image/��.png");
	LoadDivGraph("image/1st.png", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[0]);
	LoadDivGraph("image/2nd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[1]);
	LoadDivGraph("image/3rd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[2]);

	// �����̐ݒ�
	gameFont = CreateFontToHandle("GAME", 50, -1, -1);
	quizFont = CreateFontToHandle("QUIZ", 20, -1, -1);
	answerFont = CreateFontToHandle("ANSWER", 38, -1, -1);
}
void GameSceneInit(void)
{
	oCnt = 0;
	time = 1200;
	life = 3;
	stage = 0;
	gamescene = GAME_T;
	changeTime = TITLE_CHANGE;
}

int GameMain(void)
{
	int c = 0;

	cnt++;
	DrawGraph(0, 0, backImage[0][cnt / 5 % 2], true);
	DrawGraph(615, 480, lifeImage, true);
	DrawFormatStringToHandle(637, 528, 0x000000, gameFont, "%d", life);

	if (!fadeIn && !fadeOut)
	{
		switch (gamescene)
		{
		case GAME_T:
			GameTitle();
			break;
		case GAME_Q:
			QuestionScene();
			break;
		case GAME_A:
			AnswerScene();
			break;
		case GAME_R:
			c = GameResult();
			break;
		case GAME_E:
			break;
		default:
			break;
		}
	}

	return c;
}

void GameTitle(void)
{
	changeTime--;
	if (changeTime <= 0)
	{
		gamescene = GAME_Q;
		changeTime = QUESTION_CHANGE;
		Q = QuizSend(stage);
		quiz[0] = AnswerSend(stage);
		quiz[1] = Wrong1Send(stage);
		quiz[2] = Wrong2Send(stage);
		QWide = GetDrawFormatStringWidthToHandle(quizFont, Q);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000,true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(220, 233, toiImage, true);
}

void QuestionScene(void)
{
	QuestionDraw();
	changeTime--;
	if (changeTime <= 0)
	{
		time = 1200;
		gamescene = GAME_A;
		changeTime = RESULT_CHANGE;
		do {
			for (int a = 0; a < 3; a++)
			{
				A[a] = rand() % 3;
			}
		} while (A[0] == A[1] || A[1] == A[2] || A[2] == A[0]);
		for (int a = 0; a < 3; a++)
		{
			check[a] = false;
			cutA[a] = false;
			AWide[a] = GetDrawFormatStringWidthToHandle(answerFont, quiz[a]);
		}
	}
}
void QuestionDraw(void)
{
	DrawGraph(50, 25, woodImage[BIG], true);
	DrawFormatStringToHandle((700 - QWide) / 2, 83, 0xffffff, quizFont, "%s", Q);
}

void AnswerScene(void)
{
	soundOld = soundNew;
	soundNew = CheckSoundMem(cutMusic);

	if (mouseDown[MOUSE_LEFT])
	{
		if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
			A1_POS_Y < mouseY && A1_POS_Y + WOOD_SMALL_Y > mouseY)
		{
			check[0] = true;
		}
		else if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
			A2_POS_Y < mouseY && A2_POS_Y + WOOD_SMALL_Y > mouseY)
		{
			check[1] = true;
		}
		else if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
			A3_POS_Y < mouseY && A3_POS_Y + WOOD_SMALL_Y > mouseY)
		{
			check[2] = true;
		}
	}
	if (soundNew == 0 && soundOld == 1)
	{
		bool O = false;
		int okCut = 0;
		for (int a = 0; a < 3; a++)
		{
			if (check[a])
			{
				if (A[a] == 0)
				{
					O = true;
				}
				okCut++;
				cutA[a] = true;
			}
		}
		if (O)
		{
			PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
			life--;
			gamescene = GAME_R;
		}
		else if (okCut == 2)
		{
			PlaySoundMem(oMusic, DX_PLAYTYPE_BACK);
			oCnt++;
			gamescene = GAME_R;
		}
		else
		{
			PlaySoundMem(oMusic, DX_PLAYTYPE_BACK);
		}
	}

	time--;
	if (time <= 0)
	{
		PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
		life--;
		gamescene = GAME_R;
	}
	//if (oCnt % 4 == 0)
	//{
	//	fadeOut = true;
	//	fade = FADE_WHITE;
	//  stage++;
	//}
	AnswerDraw();
}
void AnswerDraw(void)
{
	QuestionDraw();

	DrawGraph(15, 480, timeImage, true);
	DrawFormatStringToHandle(24, 528, 0x000000, gameFont, "%02d", time / 60 + 1);
	
	if (!cutA[0])
	{ 
		DrawGraph(SMALL_POS_X, A1_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[0]]) / 2, A1_POS_Y + 27, 0xffffff, answerFont, "%s", quiz[A[0]]);
	}
	if (!cutA[1])
	{
		DrawGraph(SMALL_POS_X, A2_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[1]]) / 2, A2_POS_Y + 27, 0xffffff, answerFont, "%s", quiz[A[1]]);
	}
	if (!cutA[2])
	{
		DrawGraph(SMALL_POS_X, A3_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[2]]) / 2, A3_POS_Y + 27, 0xffffff, answerFont, "%s", quiz[A[2]]);
	}
}

int GameResult(void)
{
	changeTime--;
	if (changeTime <= 0)
	{
		gamescene = GAME_T;
		changeTime = TITLE_CHANGE;

		if (life <= 0)
		{
			return -1;
		}
		if (oCnt == 4)
		{
			oCnt = 0;
			stage++;
			return 1;
		}
	}

	GameResultDraw();

	return 0;
}
void GameResultDraw(void)
{
	QuestionDraw();

	if (A[0] == 0)
	{
		DrawGraph(SMALL_POS_X, A1_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[0]]) / 2, A1_POS_Y+27, 0xffffff, answerFont, "%s", quiz[A[0]]);
	}
	else if (A[1] == 0)
	{
		DrawGraph(SMALL_POS_X, A2_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[1]]) / 2, A2_POS_Y+27, 0xffffff, answerFont, "%s", quiz[A[1]]);
	}
	else if (A[2] == 0)
	{
		DrawGraph(SMALL_POS_X, A3_POS_Y, woodImage[SMALL], true);
		DrawFormatStringToHandle((700 - AWide[A[2]]) / 2, A3_POS_Y+27, 0xffffff, answerFont, "%s", quiz[A[2]]);
	}
}

int Score2(void)
{
	int O = stage * 4 + oCnt;
	if (O == 12)
	{
		return 0;
	}
	else if(O >= 4)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
int Score1(void)
{
	int O = stage * 4 + oCnt;
	if (life == 3)
	{
		return 0;
	}
	else if (O == 12)
	{
		return 1;
	}
	else if (O >= 8)
	{
		return 2;
	}
	else if (O >= 4)
	{
		return 3;
	}
	else
	{
		return 4;
	}
}