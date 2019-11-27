//=====================================
//
//PlayerActor.cpp
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerActor.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
***************************************/
PlayerActor::PlayerActor()
{
	mesh = new MeshContainer();

	ResourceManager::Instance()->GetMesh("Player", mesh);
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerActor::~PlayerActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
����������
***************************************/
void PlayerActor::Init()
{
	transform->SetPosition(Vector3::Zero);
}

/**************************************
�I������
***************************************/
void PlayerActor::Uninit()
{
}

/**************************************
�X�V����
***************************************/
void PlayerActor::Update()
{
}

/**************************************
�`�揈��
***************************************/
void PlayerActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
