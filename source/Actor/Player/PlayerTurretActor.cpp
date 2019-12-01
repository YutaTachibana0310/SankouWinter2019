//=====================================
//
//PlayerTurretActor.cpp
//�@�\:�v���C���[�C��A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerTurretActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"

/**************************************
static�����o
***************************************/
const D3DXVECTOR3 PlayerTurretActor::OffsetShot = { 0.0f, 0.0f, 3.0f };

/**************************************
�R���X�g���N�^
***************************************/
PlayerTurretActor::PlayerTurretActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("PlayerTurret", mesh);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerTurretActor::~PlayerTurretActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
����������
***************************************/
void PlayerTurretActor::Init(Transform * parent)
{
	this->parent = parent;
}

/**************************************
�I������
***************************************/
void PlayerTurretActor::Uninit()
{
	parent = nullptr;
}

/**************************************
�X�V����
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f, Vector3::Forward);
}

/**************************************
�`�揈��
***************************************/
void PlayerTurretActor::Draw()
{
	transform->SetWorld(&parent->GetMatrix());
	mesh->Draw();
}

/**************************************
���ˈʒu�擾����
***************************************/
D3DXVECTOR3 PlayerTurretActor::GetShotPosition() const
{
	D3DXMATRIX mtxWorld = transform->GetMatrix();
	mtxWorld *= parent->GetMatrix();

	D3DXVECTOR3 shotPos = { mtxWorld._41, mtxWorld._42, mtxWorld._43 };
	return shotPos + OffsetShot;
}
