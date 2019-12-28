//=====================================
//
//SpriteEffect.h
//�@�\:�X�v���C�g�`��p�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPRITEEFFECT_H_
#define _SPRITEEFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SpriteEffect : public RendererEffect
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	SpriteEffect(const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	SpriteEffect(const char*  effectPath, const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	virtual ~SpriteEffect();

	//�ύX���f����
	virtual void Commit() override;

	//���[���h�ϊ��s��ݒ菈��
	virtual void SetWorld(const D3DXMATRIX& mtxWorld);

	//�f�B�t���[�Y�ݒ菈��
	virtual void SetDiffuse(const D3DXCOLOR& color);

	//�e�N�X�`���������ݒ菈��
	virtual void SetTextureDivine(const D3DXVECTOR2& divine);

	//�e�N�X�`���ʂ��ԍ��ݒ菈��
	virtual void SetTextureIndex(int index);

	//�X�N���[�����e�s��ݒ菈��
	static void SetScreenProjection(const D3DXMATRIX& mtx);
		
protected:
	D3DXCOLOR diffuse;					//�f�B�t���[�Y
	D3DXVECTOR2 texDiv;					//�e�N�X�`��������
	D3DXVECTOR2 texSize;				//���������e�N�X�`���̃T�C�Y
	D3DXVECTOR2 uv;						//UV���W

	static D3DXMATRIX mtxScreenProj;	//�X�N���[�����e�s��

	//�V�F�[�_�ւ̃n���h��
	D3DXHANDLE hMtxScreenProj;
	D3DXHANDLE hTexUV;
	D3DXHANDLE hDiffuse;
};
#endif