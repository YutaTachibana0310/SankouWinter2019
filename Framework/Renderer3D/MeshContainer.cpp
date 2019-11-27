//=====================================
//
//���b�V���R���e�i����[MeshContainer.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MeshContainer.h"
#include "../Resource/MeshResource.h"
#include "../Effect/RendererEffect.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MeshContainer::MeshContainer() : 
	mesh(NULL),
	materialNum(0),
	resource(NULL),
	initialized(false)
{

}

/**************************************
�f�X�g���N�^
***************************************/
MeshContainer::~MeshContainer()
{
	ReleaseResource();
}

/**************************************
�`�揈��
***************************************/
void MeshContainer::Draw()
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�}�e���A���ޔ�
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < materialNum; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, textures[i]);

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&materials[i]);

		//�`��
		mesh->DrawSubset(i);
	}

	//�}�e���A������
	pDevice->SetMaterial(&matDef);
}

/**************************************
�`�揈��
***************************************/
void MeshContainer::Draw(RendererEffect & effect)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (DWORD i = 0; i < materialNum; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, textures[i]);

		//�}�e���A���ݒ�
		effect.SetMaterial(materials[i]);
		effect.Commit();

		//�`��
		mesh->DrawSubset(i);
	}
}

/**************************************
�}�e���A�����擾����
***************************************/
UINT MeshContainer::GetMaterialNum()
{
	return materialNum;
}

/**************************************
�}�e���A���擾����
***************************************/
void MeshContainer::GetMaterial(UINT index, D3DMATERIAL9& out)
{
	assert(index >= 0 && index < materialNum);
	out = materials[index];
}

/**************************************
�}�e���A���J���[�ݒ菈��
***************************************/
void MeshContainer::SetMaterialColor(const D3DXCOLOR& color, UINT index)
{
	assert(index >= 0 && index < materialNum);

	materials[index].Diffuse = color;

}

/**************************************
�}�e���A���A���t�@�ݒ菈��
***************************************/
void MeshContainer::SetMaterialAlpha(float alpha, UINT index)
{
	assert(index >= 0 && index < materialNum);
	materials[index].Diffuse.a = alpha;
}

/**************************************
���\�[�X�J������
***************************************/
void MeshContainer::ReleaseResource()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	materials.clear();

	materialNum = 0;

	if (resource != NULL)
	{
		resource->OnRelease();
		resource = NULL;
	}
}
