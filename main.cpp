#include "DxLib.h"
#include "main.h"
#include "mouse.h"
#include "effect.h"

SCENE_ID sceneID;
SCENE_ID sceneIDOld;

int mouseX;			// �}�E�X�w���W
int mouseY;			// �}�E�X�x���W
int cnt;			// �w�i�p�J�E���g
int oCnt;			// ����
int stage;		// �X�e�[�W��
int life;			// �c�@
int time;			// ��������
int A[3];			// �I��ԍ�
bool cutA[3];		// �؂��Ă邩�H
bool check;			// ���肷��H
char quiz[3];		// �I����
char Q;				// ��蕶


int gameFont;		// ���C�t�E���ԃt�H���g
int quizFont;		// ��蕶�E�I�����t�H���g

int oMusic;			// ������
int xMusic;			// �s������

int titleImage;		// �^�C�g��
int startWImage;	// �X�^�[�g�̔�
int ruleWImage;		// �V�ѕ������̔�
int backWImage;		// �߂�̔�
int ruleImage;		// �V�ѕ�����
int lifeImage;		// �c�@�̊G
int timeImage;		// ���Ԃ̊G
int toiImage;		// ���
int backImage[3][2];// �w�i[�X�e�[�W][�A�j���[�V����]
int woodImage[SIZE_END];	// ��[��E��]
int reseulImage[2];	// ���U���g[�N���A�E�I�[�o�[]
int rankImage1[5];	// �����N[S�EA�EB�EC�ED]
int rankImage2[3];	// �����N[��E���E��]

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
	
	// ���y
	oMusic = LoadSoundMem("music/O.mp3");
	xMusic = LoadSoundMem("music/X.mp3");

	// �C���X�g�����ݒ�
	{
		titleImage = LoadGraph("image/�^�C�g��.png");
		startWImage = LoadGraph("image/START.png");
		ruleWImage = LoadGraph("image/�V�ѕ�����.png");
		backWImage = LoadGraph("image/�߂�.png");
		ruleImage = LoadGraph("image/����.png");
		woodImage[0] = LoadGraph("image/���.png");
		woodImage[1] = LoadGraph("image/�I����.png");
		lifeImage = LoadGraph("image/���C�t.png");
		timeImage = LoadGraph("image/����.png");
		toiImage = LoadGraph("image/��.png");
		LoadDivGraph("image/1st.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[0]);
		LoadDivGraph("image/2nd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[1]);
		LoadDivGraph("image/3rd.jpg", 2, 2, 1, SCREEN_SIZE_X, SCREEN_SIZE_Y, backImage[2]);
	}

	// �ϐ������ݒ�
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
void SceneInit(void)	// ������
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
	// �V��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(100, 50, titleImage, true);
	DrawGraph(SMALL_POS_X, START_POS_Y, startWImage, true);
	DrawGraph(SMALL_POS_X, RULE_POS_Y, ruleWImage, true);
}

void GameScene(void)
{
	// if(��肪�o����)
	if (CheckSoundMem(cutMusic) == 0)
	{
		if (check)
		{
			// �؂��Ă���
			PlaySoundMem(oMusic, DX_PLAYTYPE_BACK);

			// �������Ⴞ��
			PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
			life--;

			check = false;
		}
	}
	if (mouseDown[MOUSE_LEFT] && !check)
	{
		// ����ł���Ȃ�
		check = true;
	}
	time--;
	if (time <= 0)
	{
		PlaySoundMem(xMusic, DX_PLAYTYPE_BACK);
		life--;
		// ���o�ĂȂ�
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