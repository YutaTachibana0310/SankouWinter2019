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
}

/**************************************
�I������
***************************************/
void FleetEnemy::Uninit()
{
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
