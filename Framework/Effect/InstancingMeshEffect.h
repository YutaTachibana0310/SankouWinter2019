//=====================================
//
// InstancingMeshEffect.h
// �@�\:���b�V���C���X�^���V���O�p�G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _INSTANCINGMESHEFFECT_H_
#define _INSTANCINGMESHEFFECT_H_

#include "../../main.h"
#include "RendererEffect.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class InstancingMeshEffect : public RendererEffect
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	InstancingMeshEffect();
	~InstancingMeshEffect();

private:
	//�V�F�[�_�ւ̃n���h��
	D3DXHANDLE hTechnique;
};

#endif