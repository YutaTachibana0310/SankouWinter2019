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
#include "../../../../Framework/Tool/DebugWindow.h"

#include "../../Player/PlayerBulletActor.h"
#include "../../../Handler/EnemyEventHandler.h"

/**************************************
コンストラクタ
***************************************/
BaseEnemy::BaseEnemy(EnemyEventHandler* handler) :
	handle(handler)
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

/**************************************
撃墜判定
***************************************/
bool BaseEnemy::IsDestroied()
{
	return hp <= 0.0f;
}

/**************************************
プレイヤーの方へ姿勢を向かせる
***************************************/
void BaseEnemy::LookAtPlayer(Transform & transform)
{
	const D3DXVECTOR3 Position = transform.GetPosition();
	const D3DXVECTOR3 Diff = handle->GetPlayerPosition() - Position;
	transform.LookAt(Position - Diff);
}

/**************************************
衝突処理
***************************************/
void BaseEnemy::OnColliderHit(ColliderObserver * other)
{
	if (typeid(*other) == typeid(PlayerBulletActor))
	{
		PlayerBulletActor *bullet = dynamic_cast<PlayerBulletActor*>(other);
		hp -= 1.0f;
		//Debug::Log("Hit");
	}
}
