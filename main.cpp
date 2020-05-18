#include "DxLib.h"
#include "main.h"
#include "game.h"
#include "mouse.h"
#include "effect.h"
#include "quiz.h"

SCENE_ID sceneID;
SCENE_ID sceneIDOld;

int mouseX;			// �}�E�X�w���W
int mouseY;			// �}�E�X�x���W
int fadeWCnt;
int rank1;
int rank2;
bool clear;

int titleImage;		// �^�C�g��
int startWImage;	// �X�^�[�g�̔�
int ruleWImage;		// �V�ѕ������̔�
int backWImage;		// �߂�̔�
int ruleImage;		// �V�ѕ�����
int resultImage[2];	// ���U���g[�N���A�E�I�[�o�[]
int rankImage1[5];	// �����N[S�EA�EB�EC�ED]
int rankImage2[3];	// �����N[��E���E��]
int EDImage[2];		//

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!SystemInit())
	{

		return 0;
	}

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (sceneID != sceneIDOld)sceneIDOld = sceneID;

		MouseCheck();

		ClsDrawScreen();					// ��ʏ���

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
					if(FadeOutW() && fadeWCnt == 3)
					{
						sceneID = SCENE_RESULT;
						PlaySoundFile("music/result.mp3", DX_PLAYTYPE_BACK);
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
			RuleScene();
			break;
		default:
			break;
		}

		MouseDraw(mouseX, mouseY);

		FadeDraw();

		ScreenFlip();						//�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɠ���ւ�
	}
	DxLib_End();							//DX���C�u�����̏I������
	return 0;								//�v���O�����̏I��
}

bool SystemInit(void)	// �����ݒ�
{
	// �V�X�e������
	SetWindowText("�V��");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				// 640*480�h�b�g,65536�F���[�h�ɐݒ�
	ChangeWindowMode(true);					// ture;window  false;�t���X�N���[��
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	// �C���X�g�����ݒ�
	titleImage = LoadGraph("image/�^�C�g��.png");
	startWImage = LoadGraph("image/START.png");
	ruleWImage = LoadGraph("image/�V�ѕ�����.png");
	backWImage = LoadGraph("image/�߂�.png");
	ruleImage = LoadGraph("image/����.png");
	resultImage[0] = LoadGraph("image/GAMEOVER.png");
	resultImage[1] = LoadGraph("image/GAMECLEAR.png");
	rankImage1[0] = LoadGraph("image/S�����N.png");
	rankImage1[1] = LoadGraph("image/A�����N.png");
	rankImage1[2] = LoadGraph("image/B�����N.png");
	rankImage1[3] = LoadGraph("image/C�����N.png");
	rankImage1[4] = LoadGraph("image/D�����N.png");
	rankImage2[0] = LoadGraph("image/��E.png");
	rankImage2[1] = LoadGraph("image/���E.png");
	rankImage2[2] = LoadGraph("image/���E.png");
	EDImage[0] = LoadGraph("image/�V��ED1.png");
	EDImage[1] = LoadGraph("image/�V��ED2.png");

	// �ϐ������ݒ�
	sceneID = SCENE_INIT;
	sceneIDOld = SCENE_MAX;
	mouseX = -1;
	mouseY = -1;
	MouseSysInit();
	FadeSysInit();
	GameSysInit();

	return true;
}
void SceneInit(void)	// ������
{
	GameSceneInit();
	QuizSceneInit();
	fadeWCnt = 0;
	clear = false;
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
	// �V��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(100, 50, titleImage, true);
	DrawGraph(SMALL_POS_X, START_POS_Y, startWImage, true);
	DrawGraph(SMALL_POS_X, RULE_POS_Y, ruleWImage, true);
}

void GameScene(void)
{
	int c;
	c = GameMain();

	if (c == -1)
	{
		// �K���I�x��
		fadeOut = true;
		fadeIn = false;
		fade = FADE_BLACK;
	}
	else if (c == 1)
	{
		// ���x���A�b�v
		fadeOut = true;
		fadeIn = false;
		fade = FADE_WHITE;
		fadeWCnt++;
	}
}

void ResultScene(void)
{
	rank1 = Score1();
	rank2 = Score2();
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
	DrawGraph(100, 25, resultImage[clear], true);
	DrawGraph(25,268,rankImage1[rank1],true);
	DrawGraph(475,268, rankImage2[rank2], true);
	DrawGraph(250, 188, EDImage[clear], true);
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