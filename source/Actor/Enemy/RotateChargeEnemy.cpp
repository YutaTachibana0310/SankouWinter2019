//=====================================
//
//RotateChargeEnemy.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RotateChargeEnemy.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Collider/BoxCollider3D.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
RotateChargeEnemy::RotateChargeEnemy()
{
	colliders.reserve(1);
	colliders.push_back(BoxCollider3D::Create("Enemy", transform));
	colliders[0]->SetSize({ 5.0f, 2.0f, 2.0f });

	ResourceManager::Instance()->GetMesh("RotateEnemy", mesh);
}

/**************************************
�f�X�g���N�^
***************************************/
RotateChargeEnemy::~RotateChargeEnemy()
{

}

/**************************************
����������
***************************************/
void RotateChargeEnemy::Init()
{
	active = true;
	SetCollider(true);
}

/**************************************
�I������
***************************************/
void RotateChargeEnemy::Uninit()
{
	SetCollider(false);
}

/**************************************
�X�V����
***************************************/
void RotateChargeEnemy::Update()
{
	transform->Rotate(5.0f, Vector3::Forward);
}

/**************************************
�`�揈��
***************************************/
void RotateChargeEnemy::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	colliders[0]->Draw();
}
