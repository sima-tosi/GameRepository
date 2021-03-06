#include "DxLib.h"
#include "main.h"
#include "game.h"
#include "mouse.h"
#include "effect.h"
#include "time.h"

SCENE_ID sceneID;	// シーン管理

int mouseX;		// マウスＸ座標
int mouseY;		// マウスＹ座標
int fadeWCnt;	// 白フェードの回数
int rank1;		// 〜ランク
int rank2;		// 〜忍
int rulePage;	// 遊び方説明のページ数
bool clear;		// ゲームクリア？
bool cutOk;		// 切ってもいい？

int titleImage;		// タイトル
int startWImage;	// スタートの板
int ruleWImage;		// 遊び方説明の板
int backWImage;		// 戻るの板
int nextWImage;		// 次への板
int ruleImage[3];	// 遊び方説明
int ayamaruImage;	// タイトル裏の彪丸
int resultImage[2];	// リザルト[クリア・オーバー]
int rankImage1[5];	// ランク[S・A・B・C・D]
int rankImage2[3];	// ランク[上・中・下]
int EDImage[2];		// ＥＤの彪丸

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!SystemInit())
	{
		return 0;
	}

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		MouseCheck();

		ClsDrawScreen();	// 画面消去

		if (fadeIn)FadeIn();

		if (mouseDown[MOUSE_LEFT] && cutOk)
		{
			MousePos(&mouseX, &mouseY);
		}

		switch (sceneID)
		{
		case SCENE_INIT:
			SceneInit();
			break;
		case SCENE_TITLE:
			if (fadeOut)
			{
				if (fade == FADE_BLACK)
				{
					if (FadeOutB())
					{
						sceneID = SCENE_GAME;
						PlaySoundFile("music/game.mp3", DX_PLAYTYPE_LOOP);
					}
				}
				if (fade == FADE_WHITE)
				{
					if (FadeOutW())
					{
						sceneID = SCENE_RULE;
					}
				}
			}
			TitleScene();
			break;
		case SCENE_GAME:
			if (fadeOut)
			{
				if (fade == FADE_BLACK)
				{
					if (FadeOutB())
					{
						sceneID = SCENE_RESULT;
						PlaySoundFile("music/resultX.mp3", DX_PLAYTYPE_BACK);
						rank1 = Score1();
						rank2 = Score2();
					}
				}
				if (fade == FADE_WHITE)
				{
					if(FadeOutW() && fadeWCnt == 3)
					{
						sceneID = SCENE_RESULT;
						PlaySoundFile("music/resultO.mp3", DX_PLAYTYPE_BACK);
						rank1 = Score1();
						rank2 = Score2();
						clear = true;
					}
				}
			}
			GameScene();
			break;
		case SCENE_RESULT:
			if (fadeOut)
			{
				if (fade == FADE_BLACK)
				{
					if (FadeOutB())
					{
						sceneID = SCENE_INIT;
					}
				}
			}
			ResultScene();
			break;
		case SCENE_RULE:
			if (fadeOut)
			{
				if (fade == FADE_WHITE)
				{
					if (FadeOutW())
					{
						sceneID = SCENE_TITLE;
					}
				}
			}
			RuleScene();
			break;
		default:
			break;
		}

		cutOk = MouseDraw(mouseX, mouseY);

		FadeDraw();

		ScreenFlip();						//バックバッファをフロントバッファと入れ替え
	}
	DxLib_End();							//DXライブラリの終了処理
	return 0;								//プログラムの終了
}

// 初期設定
bool SystemInit(void)
{
	// システム処理
	SetWindowText("彪丸");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				// 640*480ドット,65536色モードに設定
	ChangeWindowMode(true);					// ture;window  false;フルスクリーン
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	srand((unsigned int)time(NULL));

	// イラスト初期設定
	titleImage = LoadGraph("image/title.png");
	startWImage = LoadGraph("image/START.png");
	ruleWImage = LoadGraph("image/遊び方説明.png");
	backWImage = LoadGraph("image/戻る.png");
	nextWImage = LoadGraph("image/次へ.png");
	ayamaruImage = LoadGraph("image/彪丸OP.png");
	LoadDivGraph("image/説明.png", 3, 2, 2, 700, 450, ruleImage);
	LoadDivGraph("image/GAME.png", 2, 1, 2, 500, 125, resultImage);
	LoadDivGraph("image/ランク.png", 5, 1, 5, 200, 64, rankImage1);
	LoadDivGraph("image/忍1.png", 3, 1, 3, 200, 64, rankImage2);
	LoadDivGraph("image/ED彪丸.png", 2, 2, 1, 200, 225, EDImage);

	// 変数初期設定
	sceneID = SCENE_INIT;
	mouseX = -1;
	mouseY = -1;
	MouseSysInit();
	FadeSysInit();
	GameSysInit();

	return true;
}
// 初期化
void SceneInit(void)
{
	GameSceneInit();
	fadeWCnt = 0;
	clear = false;
	sceneID = SCENE_TITLE;
	PlaySoundFile("music/title.mp3", DX_PLAYTYPE_LOOP);
}

// タイトルシーン 
void TitleScene(void)
{
	if (!fadeOut)
	{
		// 開始
		if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
			START_POS_Y < mouseY && START_POS_Y + WOOD_SMALL_Y > mouseY &&
			mouseDown[MOUSE_LEFT])
		{
			fadeOut = true;
			fadeIn = false;
			fade = FADE_BLACK;
		}
		// 遊び方説明
		if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
			RULE_POS_Y < mouseY && RULE_POS_Y + WOOD_SMALL_Y > mouseY &&
			mouseDown[MOUSE_LEFT])
		{
			fadeOut = true;
			fadeIn = false;
			fade = FADE_WHITE;
			rulePage = 0;
		}
	}

	TitleDraw();
}
// タイトル描画
void TitleDraw(void)
{
	// 背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawGraph(0, 0, ayamaruImage, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(100, 50, titleImage, true);
	DrawGraph(SMALL_POS_X, START_POS_Y, startWImage, true);
	DrawGraph(SMALL_POS_X, RULE_POS_Y, ruleWImage, true);
}

// ゲームシーン
void GameScene(void)
{
	int c;
	c = GameMain();

	if (c == -1)
	{
		// ガメオベラ
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	else if (c == 1)
	{
		// レベルアップ
		fadeOut = true;
		fadeIn = false;
		fade = FADE_WHITE;
		fadeWCnt++;
	}
}

// リザルトシーン
void ResultScene(void)
{
	if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
		BACK_POS_Y < mouseY && BACK_POS_Y + WOOD_SMALL_Y > mouseY &&
		mouseDown[MOUSE_LEFT])
	{
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	ResultDraw();
}
// リザルト描画
void ResultDraw(void)
{
	DrawGraph(100, 25, resultImage[clear], true);
	DrawGraph(25,268,rankImage1[rank1],true);
	DrawGraph(475,268, rankImage2[rank2], true);
	DrawGraph(250, 188, EDImage[clear], true);
	DrawGraph(SMALL_POS_X, BACK_POS_Y, backWImage, true);
}

// ルールシーン 
void RuleScene(void)
{
	// ページをめくる
	if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
		BACK_POS_Y < mouseY && BACK_POS_Y + WOOD_SMALL_Y > mouseY &&
		mouseDown[MOUSE_LEFT] && cutOk)
	{
		rulePage++;
	}
	// タイトルに戻る
	if (rulePage == 3 && mouseDown[MOUSE_LEFT])
	{
		fadeOut = true;
		fadeIn = false;
		fade = FADE_WHITE;
	}

	RuleDraw();
}
// ルール描画
void RuleDraw(void)
{
	if (rulePage < 3)
	{
		DrawGraph(0, 0, ruleImage[rulePage], true);
	}
	else
	{
		DrawGraph(0, 0, ruleImage[2], true);
	}
	
	if (rulePage >= 2)
	{
		DrawGraph(SMALL_POS_X, BACK_POS_Y, backWImage, true);
	}
	else
	{
		DrawGraph(SMALL_POS_X, BACK_POS_Y, nextWImage, true);
	}
}