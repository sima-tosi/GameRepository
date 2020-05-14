#include "DxLib.h"
#include "main.h"
#include "mouse.h"
#include "effect.h"

SCENE_ID sceneID;
SCENE_ID sceneIDOld;

int mouseX;
int mouseY;

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

		mouseX = -1;
		mouseY = -1;

		if (mouseDown[MOUSE_LEFT]) MousePos(&mouseX, &mouseY);

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
					}
				}
				if (fade == FADE_WHITE)
				{
					FadeOutW();
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
				if (fade == FADE_WHITE)
				{
					FadeOutW();
				}
			}
			ResultScene();
			break;
		default:
			break;
		}

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

	// 変数初期設定
	sceneID = SCENE_INIT;
	sceneIDOld = SCENE_MAX;
	MouseSysInit();
	FadeSysInit();

	return true;
}
void SceneInit(void)	// 初期化
{
	sceneID = SCENE_TITLE;
}

void TitleScene(void)
{
	if (mouseDown[MOUSE_LEFT])
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
	TitleDraw();
}
void TitleDraw(void)
{
	DrawBox(0, 0, 100, 100, 0xff0000,true);
}

void GameScene(void)
{
	if (mouseDown[MOUSE_LEFT])
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
	GameDraw();
}
void GameDraw(void)
{
	DrawBox(0, 0, 100, 100, 0x00ff00,true);
}

void ResultScene(void)
{
	if (mouseDown[MOUSE_LEFT])
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
	DrawBox(0, 0, 100, 100, 0x0000ff,true);
}