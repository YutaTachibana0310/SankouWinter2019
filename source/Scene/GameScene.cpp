//=====================================
//
//GameScene.cpp
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "../BackGround/GameSkybox.h"
#include "../Actor/Player/PlayerActor.h"
#include "../Controller/PlayerBulletController.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	ResourceManager::Instance()->MakePolygon("BlazeBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });

	sceneCamera = new Camera();
	skybox = new GameSkybox();
	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	Camera::SetMainCamera(sceneCamera);

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1);
	player->onFireBullet = onFireBullet;

	player->Init();
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(skybox);
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
	player->Update();
	bulletController->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();

	player->Draw();

	bulletController->Draw();
}