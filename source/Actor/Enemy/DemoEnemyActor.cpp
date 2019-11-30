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

/**************************************
�R���X�g���N�^
***************************************/
DemoEnemyActor::DemoEnemyActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("DemoEnemy", mesh);
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
	D3DXVECTOR3 InitPos = { 50.0f, 0.0f, 0.0f };
	D3DXVECTOR3 GoalPos = { 25.0f, 0.0f, 0.0f };

	Tween::Move(*this, InitPos, GoalPos, 60, EaseType::OutCirc);
}

/**************************************
�I������
***************************************/
void DemoEnemyActor::Uninit()
{
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
