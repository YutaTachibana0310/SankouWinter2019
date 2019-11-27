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
�X�V����
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f, Vector3::Right);
}

/**************************************
�`�揈��
***************************************/
void PlayerTurretActor::Draw(const Transform & parent)
{
	transform->SetWorld(&parent.GetMatrix());
	mesh->Draw();
}
