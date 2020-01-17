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
