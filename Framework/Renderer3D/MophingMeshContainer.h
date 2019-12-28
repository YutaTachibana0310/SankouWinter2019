//=====================================
//
//MorphingMeshContainer.h
//�@�\:���[�t�B���O���b�V���R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOPHINGMESHCONTAINER_H_
#define _MOPHINGMESHCONTAINER_H_

#include "../../main.h"
#include "MeshContainer.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class MophingEffect;

/**************************************
�N���X��`
***************************************/
class MorphingMeshContainer : public MeshContainer
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	MorphingMeshContainer();
	virtual ~MorphingMeshContainer();

	//���ݕێ����Ă��郁�b�V�������[�t�e�[�u���ɓo�^����
	void RegisterVertex(unsigned index);

	//�`�揈��
	void Draw(const D3DXMATRIX& mtxWorld);

	//���݂̃��b�V����ݒ�
	void SetCurrent(unsigned index);

	//���[�t�B���O���ݒ�
	void SetNext(unsigned next);

	//�ω��ʂ�ݒ�
	void SetChange(float t);

	//�o�^�������b�V�������
	void ReleaseRegistration();

private:
	//�g�p���郁�b�V���Q
	std::vector<LPD3DXMESH> meshTable;

	//�g�p����e�N�X�`���Q
	std::vector<std::vector<LPDIRECT3DTEXTURE9>> textureContainer;

	//�g�p����}�e���A���Q
	std::vector<std::vector<D3DMATERIAL9>> materialContainer;

	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 indexBuff;

	//���_���
	DWORD fvf;
	LPDIRECT3DVERTEXDECLARATION9 declare;

	//���_�����e�[�u��
	std::vector<D3DXATTRIBUTERANGE> attributeTable;

	//�`��G�t�F�N�g
	MophingEffect *effect;

	//���[�t�B���O�C���f�b�N�X
	int currentIndex, nextIndex;

	//�ω���
	float t;

	//MeshContainer��Draw()���g�킹�����Ȃ��̂�private��
	void Draw() override;
	void Draw(RendererEffect& effect) override;
};
#endif