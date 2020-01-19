//=====================================
//
//GameMain.cpp
//機能:ゲームメイン処理
//Author:GP12B332 21 立花雄太
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
コンストラクタ
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//ゲーム内で使用するフォントを読み込み
	FontManager::Instance()->LoadFont("data/FONT/badfennec.otf");

	//サウンド読み込み
	MusicPlayer::Load();
	SoundPlayer::Instance()->Load();

	//シーンマネージャにシーンのインスタンスを追加
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene(renderTexture, renderSurface));

	//初期シーンに遷移
	const int InitScene = GameConfig::SceneID::Game;
	sceneManager->ChangeScene(InitScene);
}

/**************************************
デストラクタ
***************************************/
GameMain::~GameMain()
{
	//読み込んだフォントを解放
	FontManager::Instance()->RemoveFont("data/FONT/badfennec.otf");
}

/**************************************
更新処理
***************************************/
void GameMain::Update()
{
	BaseGame::Update();
	//Light::Update();
}