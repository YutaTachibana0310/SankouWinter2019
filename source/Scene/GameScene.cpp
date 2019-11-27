//=====================================
//
//GameScene.cpp
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../BackGround/GameSkybox.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	sceneCamera = new Camera();
	skybox = new GameSkybox();

	Camera::SetMainCamera(sceneCamera);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(skybox);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();
}