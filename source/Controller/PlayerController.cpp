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
#include "../../Framework/Core/ObjectPool.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"
#include "../Camera/GameCamera.h"
#include "../Effect/GameParticleManager.h"
#include "../Actor/Player/PlayerColliderViewer.h"
#include "../Actor/Player/PowerupItemActor.h"
#include "../Viewer/Back/BackViewer.h"
#include "../System/GameScore.h"

#include <algorithm>

/**************************************
グローバル変数
***************************************/
const float PlayerController::MaxEnergy = 100.0f;
const int PlayerController::MaxBomb = 3;
const int PlayerController::MaxLife = 2;

/**************************************
コンストラクタ
***************************************/
PlayerController::PlayerController(GameCamera *camera, BackViewer *backViewer) :
	camera(camera),
	backViewer(backViewer),
	cntEnergy(MaxEnergy),
	inSlow(false),
	cntLife(MaxLife),
	cntBomb(MaxBomb)
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	ResourceManager::Instance()->MakePolygon("PlayerCollider", "data/TEXTURE/Player/playerCollider.png", { 1.0f, 1.0f }, { 3.0f, 2.0f });
	ResourceManager::Instance()->MakePolygon("PowerupItem", "data/TEXTURE/Player/PowerupItem.png", { 3.0f, 3.0f });
	ResourceManager::Instance()->MakePolygon("PlayerShield", "data/TEXTURE/Player/PlayerShield.png", { 7.0f, 4.5f });

	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	itemContainer.reserve(5);

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	player->onFireBullet = onFireBullet;

	auto onHitPlayer = std::bind(&PlayerController::CollisionPlayer, this, std::placeholders::_1);
	player->onColliderHit = onHitPlayer;

	auto onSlowDownEnemyBullet = std::bind(&PlayerController::SlowDownEnemyBullet, this, std::placeholders::_1);
	player->onSlowdownEnemyBullet = onSlowDownEnemyBullet;

	auto onFireBomber = std::bind(&PlayerController::FireBomber, this);
	player->onFireBomber = onFireBomber;
}

/**************************************
デストラクタ
***************************************/
PlayerController::~PlayerController()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);

	Utility::DeleteContainer(itemContainer);
}

/**************************************
プレイヤー初期化
***************************************/
void PlayerController::Init()
{
	player->Init();
}

/**************************************
更新処理
***************************************/
void PlayerController::Update()
{
	player->Update();

	bulletController->Update();

	for (auto&& item : itemContainer)
	{
		item->Update();
	}

	auto itr = std::remove_if(itemContainer.begin(), itemContainer.end(), [](auto item)
	{
		return !item->IsActive();
	});
	itemContainer.erase(itr, itemContainer.end());
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

	for (auto&& item : itemContainer)
	{
		item->Draw();
	}
}

/**************************************
当たり判定描画処理
***************************************/
void PlayerController::DrawCollider()
{
	player->DrawCollider();
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
スロウダウン中かどうか
***************************************/
bool PlayerController::InSlowdown() const
{
	return inSlow;
}

/**************************************
プレイヤーの座標取得
***************************************/
D3DXVECTOR3 PlayerController::GetPlayerPosition() const
{
	return player->GetPosition();
}

/**************************************
パワーアップアイテム生成処理
***************************************/
void PlayerController::SetPowerupItem(const D3DXVECTOR3 & position)
{
	PowerupItemActor *item = ObjectPool::Instance()->Create<PowerupItemActor>();
	item->SetPosition(position);
	item->Init();
	itemContainer.push_back(item);
}

/**************************************
エナジー加算処理
***************************************/
void PlayerController::AddEnergy(float energy)
{
	cntEnergy = Math::Clamp(0.0f, MaxEnergy, cntEnergy + energy);
}

/**************************************
バレットを止める入力の処理
***************************************/
void PlayerController::SlowDownEnemyBullet(bool isSlow)
{
	if (cntEnergy > 0.0f && isSlow)
	{
		cntEnergy -= Math::Clamp(0.0f, MaxEnergy, 0.2f * FixedTime::GetTimeScale());
		EnemyTimeController::SlowDownBullet(true);
		inSlow = true;
	}
	else
	{
		EnemyTimeController::SlowDownBullet(false);
		inSlow = false;
	}
}

/**************************************
プレイヤーの当たり判定
***************************************/
void PlayerController::CollisionPlayer(ColliderObserver * other)
{
	std::string otherTag = other->Tag();
	if (otherTag == "EnemyBullet" || otherTag == "Enemy")
	{
		if (!player->IsInvincivle())
		{
			GameParticleManager::Instance()->Generate(GameEffect::PlayerExplosion, player->GetPosition());
			GameScore::Instance()->ResetCombo();

			auto callback = std::bind(&PlayerController::OnFinishCameraFocus, this);
			bool res = camera->Focus(player->GetPosition(), callback);

			if (!res)
			{
				OnFinishCameraFocus();
			}
		}
	}
	else if (otherTag == "Item")
	{
		player->PowerUp();
		backViewer->PlayPowerUp();
	}
}

/**************************************
カメラフォーカス終了時のコールバック
***************************************/
void PlayerController::OnFinishCameraFocus()
{
	if (cntLife > 0)
	{
		cntLife--;

		const D3DXVECTOR3 playerrPosition = player->GetPosition();
		int level = Math::Clamp(1, 3, player->PowerLevel());
		for (int i = 0; i < level; i++)
		{
			SetPowerupItem(playerrPosition);
		}

		TaskManager::Instance()->CreateDelayedTask(120.0f, true, [this]()
		{
			player->Init();
		});
	}

	player->Uninit();
}

/**************************************
ボンバー発射
***************************************/
void PlayerController::FireBomber()
{
	if (cntBomb <= 0)
		return;

	--cntBomb;

	D3DXVECTOR3 playerPos = player->GetPosition();
	
	playerPos.z = Math::Clamp(-50.0f, 50.0f, playerPos.z + 40.0f);

	GameParticleManager::Instance()->GenerareBomber(playerPos);

}
