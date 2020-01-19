//=====================================
//
//GameMain.cpp
//�@�\:�Q�[�����C������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"
#include "../Framework/Tool/DebugWindow.h"
#include "../Framework/Core/PlayerPrefs.h"
#include "../Framework/Light/Light.h"
#include "../Framework/Resource/FontManager.h"

#include "GameConfig.h"
#include "Sound/MusicPlayer.h"
#include "Sound/SoundPlayer.h"

#include "Scene\GameScene.h"

/**************************************
�R���X�g���N�^
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//�Q�[�����Ŏg�p����t�H���g��ǂݍ���
	FontManager::Instance()->LoadFont("data/FONT/badfennec.otf");

	//�T�E���h�ǂݍ���
	MusicPlayer::Load();
	SoundPlayer::Instance()->Load();

	//�V�[���}�l�[�W���ɃV�[���̃C���X�^���X��ǉ�
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene(renderTexture, renderSurface));

	//�����V�[���ɑJ��
	const int InitScene = GameConfig::SceneID::Game;
	sceneManager->ChangeScene(InitScene);
}

/**************************************
�f�X�g���N�^
***************************************/
GameMain::~GameMain()
{
	//�ǂݍ��񂾃t�H���g�����
	FontManager::Instance()->RemoveFont("data/FONT/badfennec.otf");
}

/**************************************
�X�V����
***************************************/
void GameMain::Update()
{
	BaseGame::Update();
	//Light::Update();
}