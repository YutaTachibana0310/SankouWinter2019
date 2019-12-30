//=====================================
//
// PlanetActor.cpp
// �@�\:�f���A�N�^�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlanetActor.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 PlanetActor::InitPos = { -500.0f, 200.0f, 200.0f };

/**************************************
�R���X�g���N�^
***************************************/
PlanetActor::PlanetActor()
{
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Planet", mesh);

	transform->SetPosition(InitPos);
}

/**************************************
�f�X�g���N�^
***************************************/
PlanetActor::~PlanetActor()
{
	SAFE_DELETE(mesh);
}

/**************************************
�X�V����
***************************************/
void PlanetActor::Update()
{

}

/**************************************
�`�揈��
***************************************/
void PlanetActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}
