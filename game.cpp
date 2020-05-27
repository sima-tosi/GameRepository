#include "DxLib.h"
#include "game.h"
#include "main.h"
#include "mouse.h"
#include "effect.h"
#include "quiz.h"

int gamescene;		

int okCnt;			// 切った枚数
int cnt;			// 背景用カウント
int oCnt;			// 正解数
int stage;			// ステージ数
int life;			// 残機
int time;			// 制限時間
int changeTime;		// シーンの変更をする時間
int A[3];			// 選択番号
int QWide;			// 問題文の幅
int AWide[3];		// 答えの幅
bool fadeinOld;		// フェードインしてる（昔）？
bool cutOkOld;		// 切ってもいいか（昔）？
bool cutA[3];		// 画面に映す？
bool check[3];		// クリックした？
char* quiz[3];		// 選択肢[正解、不正解、不正解]
char* Q;			// 問題文

int gameFont;		// ライフ・時間フォント
int quizFont;		// 問題文フォント
int answerFont;		// 選択肢フォント

int oMusic;			// 正解音
int xMusic;			// 不正解音
int quizMusic;		// 始まり音
int answerMusic;	// 選択開始音

int lifeImage;				// 残機の絵
int timeImage;				// 時間の絵
int toiImage;				// 問題
int backImage[3][2];		// 背景[ステージ][アニメーション]
int woodImage[SIZE_END];	// 板[大・小]
int ocntImage;				// 正解数のイラスト

void GameSysInit(void)
{
	// 音楽
	oMusic = LoadSoundMem("music/O.mp3");
	xMusic = LoadSoundMem("music/X.mp3");
	quizMusic = LoadSoundMem("music/quiz.mp3");
	answerMusic = LoadSoundMem("music/answer.mp3");

	// イラストの初期化
	woodImage[0] = LoadGraph("image/問題文.png");
	woodImage[1] = LoadGraph("image/選択.png");
	lifeImage = LoadGraph("image/life.jpg");
	timeImage = LoadGraph("image/time.jpg");
	toiImage = LoadGraph("image/問.png");
	ocntImage = LoadGraph("image/正解数.png");
	LoadDivGraph("image/1st.png", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[0]);
	LoadDivGraph("image/2nd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[1]);
	LoadDivGraph("image/3rd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[2]);

	// 文字の設定
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
	fadeinOld = true;
	cutOkOld = true;
	gamescene = GAME_S;
	changeTime = START_CHANGE;
}

int GameMain(void)
{
	int c = 0;

	cnt++;
	DrawGraph(0, 0, backImage[stage][cnt / 5 % 2], true);
	DrawBox(50, 0, 650, 50, 0x707070, true);
	DrawBox(50, 0, (stage * 4 + oCnt) * 50 + 50, 50, 0xff0000, true);
	DrawGraph(50, 0, ocntImage, true);
	DrawGraph(615, 480, lifeImage, true);
	DrawFormatStringToHandle(637, 528, 0x000000, gameFont, "%d", life);

	switch (gamescene)
	{
	case GAME_S:
		GameStart();
		break;
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
	case GAME_C:
		GameContnue();
		break;
	default:
		break;
	}


	fadeinOld = fadeIn;

	return c;
}

void GameStart(void)
{
	changeTime--;
	if (changeTime <= 0)
	{
		gamescene = GAME_T;
		PlaySoundMem(quizMusic, DX_PLAYTYPE_BACK);
		changeTime = TITLE_CHANGE;
	}
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
		time = 900;
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
		okCnt = 0;
		PlaySoundMem(answerMusic, DX_PLAYTYPE_BACK);
	}
}
void QuestionDraw(void)
{
	DrawGraph(50, 70, woodImage[BIG], true);
	DrawFormatStringToHandle((700 - QWide) / 2, 128, 0xffffff, quizFont, "%s", Q);
}

void AnswerScene(void)
{
	AnswerDraw();

	if (cutOk && !cutOkOld)
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
			return;
		}
		else if (okCut != okCnt)
		{
			PlaySoundMem(oMusic, DX_PLAYTYPE_BACK);
			okCnt++;
			if (okCut == 2)
			{
				oCnt++;
				gamescene = GAME_R;
				return;
			}
		}
	}

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

	time--;
	if (time <= 0)
	{
		for (int a = 0; a < 3; a++)
		{
			if (check[a] != cutA[a])
			{
				return;
			}
		}
		PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
		life--;
		gamescene = GAME_R;
		return;
	}

	cutOkOld = cutOk;
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
		gamescene = GAME_C;

		if (life <= 0)
		{
			return -1;
		}
		if (oCnt == 4)
		{
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

void GameContnue(void)
{
	if (fadeOut)
	{
		return;
	}
	else if (fadeIn)
	{
		if (!fadeinOld && fade == FADE_WHITE)
		{
			oCnt = 0;
			stage++;
			gamescene = GAME_S; 
			changeTime = START_CHANGE;
		}
		return;
	}
	else
	{
		gamescene = GAME_T;
		PlaySoundMem(quizMusic, DX_PLAYTYPE_BACK);
		changeTime = TITLE_CHANGE;
	}
}

// ～忍
int Score2(void)
{
	int O = stage * 4 + oCnt;
	if (O == 12)
	{
		return 0;
	}
	else if(O >= 6)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
// ～ランク
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