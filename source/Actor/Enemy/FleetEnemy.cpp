//=====================================
//
// FleetEnemy.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FleetEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Core/ObjectPool.h"

#include "../../System/EnemyTween.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
FleetEnemy::FleetEnemy(EnemyHandler* handler) :
	BaseBigEnemy(handler)
{	
	ResourceManager::Instance()->GetMesh("FleetEnemy", mesh);

	colliders.reserve(0);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 10.0f, 10.0f });
	colliders[0]->AddObserver(this);
}

/**************************************gae
�f�X�g���N�^
***************************************/
FleetEnemy::~FleetEnemy()
{
}

/**************************************
����������
***************************************/
void FleetEnemy::Init()
{
	active = true;
	SetCollider(true);

	D3DXVECTOR3 InitPos = { 0.0f, -10.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, -10.0f, 25.0f };

	EnemyTween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	SetCollider(true);

	hp = 50.0f;
	active = true;

	isDestroied = false;
}

/**************************************
�I������
***************************************/
void FleetEnemy::Uninit()
{
	BaseBigEnemy::Uninit();

	SetCollider(false);
	active = false;
	ObjectPool::Instance()->Destroy<FleetEnemy>(this);
}

/**************************************
�X�V����
***************************************/
void FleetEnemy::Update()
{

}

/**************************************
�`�揈��
***************************************/
void FleetEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}
