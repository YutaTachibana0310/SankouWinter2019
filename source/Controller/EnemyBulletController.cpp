//=====================================
//
// EnemyBulletController.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyBulletController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Core/ObjectPool.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../Actor/Enemy/EnemyBulletActor.h"

#include <algorithm>

/**************************************
グローバル変数
***************************************/
const unsigned EnemyBulletController::MaxBullet = 4096;

/**************************************
コンストラクタ
***************************************/
EnemyBulletController::EnemyBulletController() :
	cntBullet(0)
{
	bulletContainer.reserve(4096);

	ResourceManager::Instance()->MakePolygon(
		"EnemyBullet",
		"data/TEXTURE/Enemy/EnemyBullet.png",
		{ 2.0f, 2.0f },
		{ 8.0f, 8.0f });
}

/**************************************
デストラクタ
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	Utility::DeleteContainer(bulletContainer);
}

/**************************************
更新処理
***************************************/
void EnemyBulletController::Update()
{
	//更新
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	//非アクティブになったバレットをObjectPoolへ移動
	std::for_each(bulletContainer.begin(), bulletContainer.end(), [](auto bullet)
	{
		if (bullet->IsActive())
			return;

		ObjectPool::Instance()->Destroy<EnemyBulletActor>(bullet);
		bullet = nullptr;
	});

	//削除したバレットをコンテナから除外
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return ptr == nullptr;
	});
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
描画処理
***************************************/
void EnemyBulletController::Draw()
{
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}
}

/**************************************
バレットセット処理
***************************************/
void EnemyBulletController::SetBullet(const Transform & shotTransform)
{
	if (cntBullet > MaxBullet)
	{
		Debug::Log("EnemyBullet is Max");
		return;
	}

	EnemyBulletActor* bullet = ObjectPool::Instance()->Create<EnemyBulletActor>();
	bullet->Init(shotTransform);

	bulletContainer.push_back(bullet);
}
