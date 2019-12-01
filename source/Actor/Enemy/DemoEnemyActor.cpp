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
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Collider/BoxCollider3D.h"

/**************************************
�R���X�g���N�^
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);

	collider = BoxCollider3D::Create("Enemy", transform);
	collider->AddObserver(this);
	collider->SetSize({ 5.0f, 8.0f, 7.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
DemoEnemyActor::~DemoEnemyActor()
{
	SAFE_DELETE(mesh);
	collider.reset();
}

/**************************************
����������
***************************************/
void DemoEnemyActor::Init()
{
	D3DXVECTOR3 InitPos = { 0.0f, 0.0f, 50.0f };
	D3DXVECTOR3 GoalPos = { 0.0f, 0.0f, 25.0f };

	Tween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);

	collider->SetActive(true);
}

/**************************************
�I������
***************************************/
void DemoEnemyActor::Uninit()
{
	collider->SetActive(false);

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

#ifdef _DEBUG
	collider->Draw();
#endif
}

/**************************************
�����蔻�菈��
***************************************/
void DemoEnemyActor::OnColliderHit(ColliderObserver * other)
{
}
