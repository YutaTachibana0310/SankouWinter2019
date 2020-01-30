//=====================================
//
//TitleViewer.cpp
//�@�\:�^�C�g���r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitleViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TitleViewer::TitleViewer()
{
	titleLogo = new Polygon2D();
	titleLogo->LoadTexture("data/TEXTURE/Viewer/TitleLogo.png");
	titleLogo->SetSize({ 512.0f, 128.0f });
	titleLogo->SetPosition({ SCREEN_CENTER_X, 360.0f, 0.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(titleLogo);
}

/**************************************
�X�V����
***************************************/
void TitleViewer::Update()
{

}

/**************************************
�`�揈��
***************************************/
void TitleViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	titleLogo->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
