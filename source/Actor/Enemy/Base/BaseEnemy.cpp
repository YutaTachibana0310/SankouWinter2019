//=====================================
//
//BaseEnemy.cpp
//�@�\:�G�l�~�[���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEnemy.h"
#include "../../../../Framework/Collider/BoxCollider3D.h"
#include "../../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../../Framework/Tool/DebugWindow.h"

#include "../../Player/PlayerBulletActor.h"
#include "../../../Handler/EnemyEventHandler.h"

/**************************************
�R���X�g���N�^
***************************************/
BaseEnemy::BaseEnemy(EnemyEventHandler* handler) :
	handle(handler)
{
	mesh = new MeshContainer();
}

/**************************************
�f�X�g���N�^
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
�����蔻��ݒ�
***************************************/
void BaseEnemy::SetCollider(bool state)
{
	for (auto&& collider : colliders)
	{
		collider->SetActive(state);
	}
}

/**************************************
���Ĕ���
***************************************/
bool BaseEnemy::IsDestroied()
{
	return hp <= 0.0f;
}

/**************************************
�v���C���[�̕��֎p������������
***************************************/
void BaseEnemy::LookAtPlayer(Transform & transform)
{
	const D3DXVECTOR3 Position = transform.GetPosition();
	const D3DXVECTOR3 Diff = handle->GetPlayerPosition() - Position;
	transform.LookAt(Position - Diff);
}

/**************************************
�Փˏ���
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
