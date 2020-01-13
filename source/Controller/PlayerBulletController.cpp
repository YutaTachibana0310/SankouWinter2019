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
#include "../../Framework/Resource/ResourceManager.h"

#include "../Actor/Player/PlayerBulletActor.h"

#include <algorithm>
#include <functional>

/**************************************
コンストラクタ
***************************************/
PlayerBulletController::PlayerBulletController()
{
	ResourceManager::Instance()->MakePolygon("PlayerBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });
	ResourceManager::Instance()->MakePolygon("PlayerBulletMain", "data/TEXTURE/Player/PlayerMainBullet.png", { 3.0f, 1.5f });
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	std::sort(bulletContainer.begin(), bulletContainer.end(), std::greater<>());
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
発射処理
***************************************/
void PlayerBulletController::FireBullet(const D3DXVECTOR3 & pos, bool isMain)
{
	PlayerBulletActor* bullet = ObjectPool::Instance()->Create<PlayerBulletActor>();
	bullet->Init(pos, isMain);
	bulletContainer.push_back(bullet);
}
