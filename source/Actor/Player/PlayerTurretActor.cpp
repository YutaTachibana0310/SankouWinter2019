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
�X�V����
***************************************/
void PlayerTurretActor::Update()
{
	transform->Rotate(-2.0f * FixedTime::GetTimeScale(), Vector3::Forward);
}

/**************************************
�`�揈��
***************************************/
void PlayerTurretActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

/**************************************
���ˈʒu�擾����
***************************************/
D3DXVECTOR3 PlayerTurretActor::GetShotPosition() const
{
	return transform->GetPosition() + OffsetShot;
}

/**************************************
PlayerTurretRoot�X�V����
***************************************/
void PlayerTurretRoot::Update()
{
	const float AngleRotateTurret = 3.0f;
	transform->Rotate(AngleRotateTurret * FixedTime::GetTimeScale(), Vector3::Forward);
}
