//=====================================
//
//PlayerController.cpp
//機能:プレイヤーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PlayerController::PlayerController()
{
	ResourceManager::Instance()->MakePolygon("PlayerBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	
	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1);
	player->onFireBullet = onFireBullet;

	player->Init();
}

/**************************************
デストラクタ
***************************************/
PlayerController::~PlayerController()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);
}

/**************************************
更新処理
***************************************/
void PlayerController::Update()
{
	player->Update();

	bulletController->Update();
}

/**************************************
描画処理
***************************************/
void PlayerController::Draw()
{
	player->Draw();
}

/**************************************
バレット描画処理
***************************************/
void PlayerController::DrawBullet()
{
	bulletController->Draw();
}
