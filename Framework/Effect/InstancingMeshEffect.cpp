//=====================================
//
//���b�V���C���X�^���V���O�p�̃G�t�F�N�g����[InstancingMeshEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "InstancingMeshEffect.h"
#include "../Resource/ResourceManager.h"
#include "../Light/Light.h"

/**************************************
�R���X�g���N�^
***************************************/
InstancingMeshEffect::InstancingMeshEffect()
{
	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/InstancingMesh.cfx", effect);

	//�n���h���擾
	hView = effect->GetParameterByName(0, "mtxView");
	hProjection = effect->GetParameterByName(0, "mtxProjection");

	hMatDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMatAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMatSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);
}

/**************************************
�f�X�g���N�^
***************************************/
InstancingMeshEffect::~InstancingMeshEffect()
{
	SAFE_RELEASE(effect);
}
