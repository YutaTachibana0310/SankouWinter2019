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
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Task/TaskManager.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"
#include "../Camera/GameCamera.h"
#include "../Effect/GameParticleManager.h"

/**************************************
グローバル変数
***************************************/
const float PlayerController::MaxEnergy = 100.0f;
const int PlayerController::MaxBomb = 3;
const int PlayerController::MaxLife = 2;

/**************************************
コンストラクタ
***************************************/
PlayerController::PlayerController(GameCamera *camera) :
	camera(camera),
	cntEnergy(MaxEnergy),
	cntLife(MaxLife),
	cntBomb(MaxBomb)
{
	ResourceManager::Instance()->MakePolygon("PlayerBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	
	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1);
	player->onFireBullet = onFireBullet;

	auto onHitPlayer = std::bind(&PlayerController::CollisionPlayer, this, std::placeholders::_1);
	player->onColliderHit = onHitPlayer;

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
エナジーの残り割合取得処理
***************************************/
float PlayerController::GetPercentEnergy() const
{
	return cntEnergy / MaxEnergy;
}

/**************************************
残機数取得処理
***************************************/
int PlayerController::GetCntLife() const
{
	return cntLife;
}

/**************************************
ボンバー残数取得処理
***************************************/
int PlayerController::GetCntBomb() const
{
	return cntBomb;
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

/**************************************
プレイヤーの当たり判定
***************************************/
void PlayerController::CollisionPlayer(ColliderObserver * other)
{
	GameParticleManager::Instance()->Generate(GameEffect::PlayerExplosion, player->GetPosition());	

	auto callback = std::bind(&PlayerController::OnFinishCameraFocus, this);
	bool res = camera->Focus(player->GetPosition(), callback);

	if (!res)
	{
		OnFinishCameraFocus();
	}
}

/**************************************
カメラフォーカス終了時のコールバック
***************************************/
void PlayerController::OnFinishCameraFocus()
{
	player->Uninit();

	if (cntLife > 0)
	{
		cntLife--;
		TaskManager::Instance()->CreateDelayedTask(120.0f, true, [this]()
		{
			player->Init();
		});
	}
}
