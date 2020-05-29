#pragma once

// 定義
#define SCREEN_SIZE_X	700		// 画面横サイズ
#define SCREEN_SIZE_Y	600		// 画面縦サイズ
#define WOOD_SMALL_X	500		// 小さい木の横サイズ
#define WOOD_SMALL_Y	100		// 小さい木の縦サイズ

#define SMALL_POS_X	100			// 小さい木の横座標
#define BIG_WOOD_X	 50			// 大きい木の横座標
#define START_POS_Y	325			// スタートの縦座標
#define RULE_POS_Y	450			// 遊び方説明の縦座標
#define BACK_POS_Y	475			// 戻る・次への縦座標

// シーン管理
enum SCENE_ID
{
	SCENE_INIT,		// 初期設定
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// プレイ中
	SCENE_RESULT,	// リザルト
	SCENE_RULE,		// ルール
	SCENE_MAX		
};
// 木のサイズ
enum SIZE_WOOD {
	BIG,			// 大きい
	SMALL,			// 小さい
	SIZE_END
};

// プロトタイプ宣言
bool SystemInit(void);	// 初期設定
void SceneInit(void);	// 初期化
void TitleScene(void);	// タイトルシーン
void TitleDraw(void);	// タイトル描画
void GameScene(void);	// ゲームシーン
void ResultScene(void);	// リザルトシーン
void ResultDraw(void);	// リザルト描画
void RuleScene(void);	// ルールシーン
void RuleDraw(void);	// ルール描画

extern int mouseX;			// マウスＸ座標
extern int mouseY;			// マウスＹ座標
extern bool cutOk;			// 切ってもいい