//=====================================
//
//BaseEnemy.cpp
//機能:エネミー基底クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEnemy.h"
#include "../../../../Framework/Collider/BoxCollider3D.h"
#include "../../../../Framework/Renderer3D/MeshContainer.h"

/**************************************
コンストラクタ
***************************************/
BaseEnemy::BaseEnemy()
{
	mesh = new MeshContainer();
}

/**************************************
デストラクタ
***************************************/
BaseEnemy::~BaseEnemy()
{
	SAFE_DELETE(mesh);

	for (auto&& collider : colliders)
	{
		collider.reset();
	}
}

/**************************************
当たり判定設定
***************************************/
void BaseEnemy::SetCollider(bool state)
{
	for (auto&& collider : colliders)
	{
		collider->SetActive(state);
	}
}
