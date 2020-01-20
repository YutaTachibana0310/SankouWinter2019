//=====================================
//
//BackViewer.cpp
//�@�\:�w�iUI�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackViewer.h"
#include "TimeBreakText.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BackViewer::BackViewer()
{
	timeBreak = new TimeBreakText();
}

/**************************************
�f�X�g���N�^
***************************************/
BackViewer::~BackViewer()
{
	SAFE_DELETE(timeBreak);
}

/**************************************
�`�揈��
***************************************/
void BackViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	timeBreak->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
TimeBreak�Đ�����
***************************************/
void BackViewer::PlayTimeBreak()
{
	timeBreak->Set();
}
