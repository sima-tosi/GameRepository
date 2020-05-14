#pragma once

// 定義
#define SCREEN_SIZE_X 700
#define SCREEN_SIZE_Y 600

// シーン管理
enum SCENE_ID
{
	SCENE_INIT,		// 初期設定
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// プレイ中
	SCENE_RESULT,	// リザルト
	SCENE_MAX		
};

// プロトタイプ宣言

bool SystemInit(void);
void SceneInit(void);
void TitleScene(void);
void TitleDraw(void);
void GameScene(void);
void GameDraw(void);
void ResultScene(void);
void ResultDraw(void);