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

/**************************************
�R���X�g���N�^
***************************************/
BaseEnemy::BaseEnemy()
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
