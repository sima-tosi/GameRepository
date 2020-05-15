#include "DxLib.h"
#include "main.h"
#include "mouse.h"
#include "effect.h"

SCENE_ID sceneID;
SCENE_ID sceneIDOld;

int mouseX;			// マウスＸ座標
int mouseY;			// マウスＹ座標
int cnt;			// 背景用カウント
int oCnt;			// 正解数
int stage;		// ステージ数
int life;			// 残機
int time;			// 制限時間
int A[3];			// 選択番号
bool cutA[3];		// 切ってるか？
bool check;			// 判定する？
char quiz[3];		// 選択肢
char Q;				// 問題文


int gameFont;		// ライフ・時間フォント
int quizFont;		// 問題文・選択肢フォント

int oMusic;			// 正解音
int xMusic;			// 不正解音

int titleImage;		// タイトル
int startWImage;	// スタートの板
int ruleWImage;		// 遊び方説明の板
int backWImage;		// 戻るの板
int ruleImage;		// 遊び方説明
int lifeImage;		// 残機の絵
int timeImage;		// 時間の絵
int toiImage;		// 問題
int backImage[3][2];// 背景[ステージ][アニメーション]
int woodImage[SIZE_END];	// 板[大・小]
int reseulImage[2];	// リザルト[クリア・オーバー]
int rankImage1[5];	// ランク[S・A・B・C・D]
int rankImage2[3];	// ランク[上・中・下]

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!SystemInit())
	{

		return 0;
	}

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (sceneID != sceneIDOld)sceneIDOld = sceneID;

		MouseCheck();

		ClsDrawScreen();					// 画面消去

		if (fadeIn)FadeIn();

		if (mouseDown[MOUSE_LEFT])
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
						PlaySoundFile("music/result.mp3", DX_PLAYTYPE_BACK);
					}
				}
				if (fade == FADE_WHITE)
				{
					FadeOutW();
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
			RuleScene();
			break;
		default:
			break;
		}

		MouseDraw(mouseX, mouseY);

		FadeDraw();

		ScreenFlip();						//バックバッファをフロントバッファと入れ替え
	}
	DxLib_End();							//DXライブラリの終了処理
	return 0;								//プログラムの終了
}

bool SystemInit(void)	// 初期設定
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
	
	// 音楽
	oMusic = LoadSoundMem("music/O.mp3");
	xMusic = LoadSoundMem("music/X.mp3");

	// イラスト初期設定
	{
		titleImage = LoadGraph("image/タイトル.png");
		startWImage = LoadGraph("image/START.png");
		ruleWImage = LoadGraph("image/遊び方説明.png");
		backWImage = LoadGraph("image/戻る.png");
		ruleImage = LoadGraph("image/説明.png");
		woodImage[0] = LoadGraph("image/問題.png");
		woodImage[1] = LoadGraph("image/選択肢.png");
		lifeImage = LoadGraph("image/ライフ.png");
		timeImage = LoadGraph("image/時間.png");
		toiImage = LoadGraph("image/問.png");
		LoadDivGraph("image/1st.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[0]);
		LoadDivGraph("image/2nd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[1]);
		LoadDivGraph("image/3rd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[2]);
	}

	// 変数初期設定
	sceneID = SCENE_INIT;
	sceneIDOld = SCENE_MAX;
	mouseX = -1;
	mouseY = -1;
	MouseSysInit();
	FadeSysInit();

	gameFont = CreateFontToHandle("GAME", 50, 3, -1);
	quizFont = CreateFontToHandle("QUIZ", 70, 1, -1);

	return true;
}
void SceneInit(void)	// 初期化
{
	oCnt = 0;
	time = 1200;
	life = 3;
	check = false;
	stage = 1;

	sceneID = SCENE_TITLE;
	PlaySoundFile("music/title.mp3", DX_PLAYTYPE_LOOP);
}

void TitleScene(void)
{
	if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
		START_POS_Y < mouseY && START_POS_Y + WOOD_SMALL_Y > mouseY &&
		mouseDown[MOUSE_LEFT])
	{
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
		RULE_POS_Y < mouseY && RULE_POS_Y + WOOD_SMALL_Y > mouseY &&
		mouseDown[MOUSE_LEFT])
	{
		sceneID = SCENE_RULE;
	}

	TitleDraw();
}
void TitleDraw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	// 彪丸
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(100, 50, titleImage, true);
	DrawGraph(SMALL_POS_X, START_POS_Y, startWImage, true);
	DrawGraph(SMALL_POS_X, RULE_POS_Y, ruleWImage, true);
}

void GameScene(void)
{
	// if(問題が出たら)
	if (CheckSoundMem(cutMusic) == 0)
	{
		if (check)
		{
			// 切っていい
			PlaySoundMem(oMusic, DX_PLAYTYPE_BACK);

			// きっちゃだめ
			PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
			life--;

			check = false;
		}
	}
	if (mouseDown[MOUSE_LEFT] && !check)
	{
		// 判定できるなら
		check = true;
	}
	time--;
	if (time <= 0)
	{
		PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
		life--;
		// 問題出てない
	}

	//if (oCnt % 4 == 0)
	//{
	//	fadeOut = true;
	//	fade = FADE_WHITE;
	//  stage++;
	//}
	if (life <= 0)
	{
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	if (mouseDown[MOUSE_RIGHT])
	{
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	GameDraw();
}
void GameDraw(void)
{
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);*/

	cnt++;
	DrawGraph(0, 0, backImage[stage][cnt/5%2], true);

	DrawGraph(75, 180, timeImage, true);
	DrawFormatStringToHandle(200, 185, 0x000000,gameFont, "%d", time / 60);
	DrawGraph(425, 180, lifeImage, true);
	DrawFormatStringToHandle(550, 185, 0x000000,gameFont, "%d", life);

	DrawGraph(50, 15, woodImage[BIG], true);
	DrawFormatStringToHandle(50, 15, 0xffffff, quizFont, "%s", Q);
	DrawGraph(SMALL_POS_X, A1_POS_Y, woodImage[SMALL], true);
	DrawFormatStringToHandle(SMALL_POS_X, A1_POS_Y, 0xffffff, quizFont, "%s", quiz[0]);
	DrawGraph(SMALL_POS_X, A2_POS_Y, woodImage[SMALL], true);
	DrawFormatStringToHandle(SMALL_POS_X, A2_POS_Y, 0xffffff, quizFont, "%s", quiz[1]);
	DrawGraph(SMALL_POS_X, A3_POS_Y, woodImage[SMALL], true);
	DrawFormatStringToHandle(SMALL_POS_X, A3_POS_Y, 0xffffff, quizFont, "%s", quiz[2]);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawGraph(220, 233, toiImage, true);
}

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
	if (mouseDown[MOUSE_RIGHT])
	{
		fadeOut = true;
		fade = FADE_WHITE;
	}
	ResultDraw();
}
void ResultDraw(void)
{
	DrawGraph(SMALL_POS_X, BACK_POS_Y, backWImage, true);
}

void RuleScene(void)
{
	if (SMALL_POS_X < mouseX && SMALL_POS_X + WOOD_SMALL_X > mouseX &&
		BACK_POS_Y < mouseY && BACK_POS_Y + WOOD_SMALL_Y > mouseY &&
		mouseDown[MOUSE_LEFT])
	{
		sceneID = SCENE_TITLE;
	}

	RuleDraw();
}
void RuleDraw(void)
{
	DrawGraph(0, 0, ruleImage, true);
	DrawGraph(SMALL_POS_X, BACK_POS_Y, backWImage, true);
}