//=====================================
//
//DemoEnemyActor.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoEnemyActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

#include "../../Effect/GameParticleManager.h"
#include "../../System/EnemyTween.h"

/**************************************
�R���X�g���N�^
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	colliders.resize(1, nullptr);
	colliders[0] = BoxCollider3D::Create("Enemy", transform);
	colliders[0]->AddObserver(this);
	colliders[0]->SetSize({ 5.0f, 8.0f, 7.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
����������
***************************************/
void DemoEnemyActor::Init()
{
	D3DXVECTOR3 InitPos = { 0.0f, 0.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, 0.0f, 25.0f };

	EnemyTween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	SetCollider(true);

	hp = 50.0f;
}

/**************************************
�I������
***************************************/
void DemoEnemyActor::Uninit()
{
	SetCollider(false);

	//���p�ɍŏ���������
	Init();
}

/**************************************
�X�V����
***************************************/
void DemoEnemyActor::Update()
{

}

/**************************************
�`�揈��
***************************************/
void DemoEnemyActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
�����蔻�菈��
***************************************/
void DemoEnemyActor::OnColliderHit(ColliderObserver * other)
{
	hp -= 1.0f;

	if (hp <= 0)
	{
		GameParticleManager::Instance()->GenerateEnemyExplostion(transform->GetPosition());
		Uninit();
	}
}
