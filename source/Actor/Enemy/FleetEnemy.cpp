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

#include "../../System/EnemyTween.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
FleetEnemy::FleetEnemy()
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
}

/**************************************
�I������
***************************************/
void FleetEnemy::Uninit()
{
	SetCollider(false);

	//���p�ɍŏ���������
	Init();
}

/**************************************
�X�V����
***************************************/
void FleetEnemy::Update()
{
	if (hp <= 0)
	{
		GameParticleManager::Instance()->GenerateEnemyBigExplosion(transform->GetPosition());
		Uninit();
	}
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
