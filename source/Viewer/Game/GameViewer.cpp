//=====================================
//
// GameViewer.cpp
// �@�\:�Q�[���r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

#include "ScoreViewer.h"
#include "EnergyViewer.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
GameViewer::GameViewer()
{
	bg = new Polygon2D();
	bg->SetSize({ (float)SCREEN_WIDTH / 2.0f, (float)55.0f});
	bg->SetPosition({ SCREEN_CENTER_X, 55.0f, 0.0f });
	bg->LoadTexture("data/TEXTURE/Viewer/ViewerBelt.png");
	bg->SetUV(0.0f, 0.0f, 1.0f, 1.0f);

	scoreViewer = new ScoreViewer();
	energyViewer = new EnergyViewer();
}

/**************************************
�f�X�g���N�^
***************************************/
GameViewer::~GameViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(scoreViewer);
	SAFE_DELETE(energyViewer);
}

/**************************************
�X�V����
***************************************/
void GameViewer::Update()
{
	scoreViewer->Update();
	energyViewer->Update();
}

/**************************************
�`�揈��
***************************************/
void GameViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	bg->Draw();

	scoreViewer->Draw();

	energyViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
