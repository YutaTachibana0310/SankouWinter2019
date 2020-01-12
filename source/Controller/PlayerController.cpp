//=====================================
//
//PlayerController.cpp
//機能:プレイヤーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Input/input.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/
const float PlayerController::MaxEnergy = 100.0f;

/**************************************
コンストラクタ
***************************************/
PlayerController::PlayerController() :
	cntEnergy(100.0f)
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
	InputEnemyBulletSlowDown();

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

/**************************************
バレットを止める入力の処理
***************************************/
void PlayerController::InputEnemyBulletSlowDown()
{
	if (Keyboard::GetPress(DIK_X) && cntEnergy >= 0.0f)
	{
		cntEnergy -= Math::Clamp(0.0f, MaxEnergy, 0.2f * FixedTime::GetTimeScale());
		EnemyTimeController::SlowDownBullet(true);
	}
	else
	{
		EnemyTimeController::SlowDownBullet(false);
	}
}
