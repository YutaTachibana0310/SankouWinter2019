//=====================================
//
//���b�V���R���e�i�w�b�_[MeshContainer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class MeshResource;
class RendererEffect;

/**************************************
�N���X��`
***************************************/
class MeshContainer
{
	friend class MeshResource;
public:
	MeshContainer();								//�R���X�g���N�^
	virtual ~MeshContainer();						//�f�X�g���N�^

	virtual void ReleaseResource();					//���\�[�X�������

	virtual void Draw();							//���f����`��
	virtual void Draw(RendererEffect& effect);		//���f����`��i�V�F�[�_�g�p)

	virtual UINT GetMaterialNum();
	virtual void GetMaterial(UINT index, D3DMATERIAL9& out);
	virtual void SetMaterialColor(const D3DXCOLOR& color, UINT index);
	virtual void SetMaterialAlpha(float alpha, UINT index);

protected:								
	LPD3DXMESH mesh;								//���b�V���f�[�^
	std::vector<D3DMATERIAL9> materials;			//�}�e���A�����
	std::vector<LPDIRECT3DTEXTURE9> textures;		//�e�N�X�`��
	DWORD materialNum;								//�}�e���A����

private:
	MeshResource * resource;						//���\�[�X�̎Q�ƌ�
	bool initialized;								//���b�V�����������ς݂��ǂ���

};

#endif