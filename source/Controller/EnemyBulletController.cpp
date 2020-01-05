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

#include "../../Library/nameof/nameof.hpp"

#include "../Actor/Enemy/EnemyBulletActor.h"

#include <algorithm>

#include "../Handler/EnemyBulletHandler.h"

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
		EnemyBulletConfig::SizePolygon,
		EnemyBulletConfig::SplitTexture);
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
	});

	//削除したバレットをコンテナから除外
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return !ptr->IsActive();
	});
	bulletContainer.erase(itr, bulletContainer.end());

	//デバッグメニュー
	Debug::Begin("EnemyBullet");
	static int bulletType = EnemyBulletConfig::Type(0);

	if (Debug::Button("Shot"))
	{
		Transform transform;
		SetBullet(transform,  EnemyBulletConfig::Type(bulletType), 0.5f);
	}

	if (Debug::Button("Way Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetWayBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 5, 60);
	}

	if (Debug::Button("Circle Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetCircleBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 16);
	}

	if (Debug::Button("Strew Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetStrewBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 30.0f);
	}

	for (int i = 0; i < EnemyBulletConfig::Type::EnemyBulletMax; i++)
	{
		std::string label = std::string(NAMEOF_ENUM(EnemyBulletConfig::Type(i)));
		Debug::RadioButton(label.c_str(), bulletType, i);
	}

	Debug::End();
}

/**************************************
描画処理
***************************************/
void EnemyBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	for (auto&& bullet : bulletContainer)
	{
		bullet->DrawBloom();
	}

	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
バレットセット処理
***************************************/
void EnemyBulletController::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	if (cntBullet > MaxBullet)
	{
		Debug::Log("EnemyBullet is Max");
		return;
	}

	EnemyBulletActor* bullet = ObjectPool::Instance()->Create<EnemyBulletActor>();
	bullet->Init(shotTransform);

	bullet->SetType(type);
	bullet->SetSpeed(speed);

	bulletContainer.push_back(bullet);
}
