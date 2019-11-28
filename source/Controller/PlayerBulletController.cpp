//=====================================
//
//PlayerBulletController.cpp
//機能:プレイヤーバレットコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Core/ObjectPool.h"

#include "../Actor/Player/PlayerBulletActor.h"

#include <algorithm>

/**************************************
コンストラクタ
***************************************/
PlayerBulletController::PlayerBulletController()
{
}

/**************************************
デストラクタ
***************************************/
PlayerBulletController::~PlayerBulletController()
{
	Utility::DeleteContainer(bulletContainer);
}

/**************************************
更新処理
***************************************/
void PlayerBulletController::Update()
{
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	for (auto&& bullet : bulletContainer)
	{
		if (bullet->IsActive())
			continue;

		bullet->Uninit();
		ObjectPool::Instance()->Destroy(bullet);
		bullet = nullptr;
	}

	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto bullet) {return bullet == nullptr; });
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
描画処理
***************************************/
void PlayerBulletController::Draw()
{
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}
}

/**************************************
発射処理
***************************************/
void PlayerBulletController::FireBullet(const D3DXVECTOR3 & pos)
{
	PlayerBulletActor* bullet = ObjectPool::Instance()->Create<PlayerBulletActor>();
	bullet->Init(pos);
	bulletContainer.push_back(bullet);
}
