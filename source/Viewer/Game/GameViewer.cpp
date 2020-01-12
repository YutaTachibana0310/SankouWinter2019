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
#include "BomberViewer.h"
#include "LifeViewer.h"

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
	bomberViewer = new BomberViewer();
	lifeViewer = new LifeViewer();
}

/**************************************
�f�X�g���N�^
***************************************/
GameViewer::~GameViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(scoreViewer);
	SAFE_DELETE(energyViewer);
	SAFE_DELETE(bomberViewer);
	SAFE_DELETE(lifeViewer);
}

/**************************************
�X�V����
***************************************/
void GameViewer::Update()
{
	scoreViewer->Update();
	energyViewer->Update();
	bomberViewer->Update();
	lifeViewer->Update();
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

	bomberViewer->Draw();

	lifeViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

/**************************************
�`��p�����[�^�ݒ菈��
***************************************/
void GameViewer::SetParameter(const GameViewerParameter & param)
{
	energyViewer->SetPercent(param.percentEnergy);
	bomberViewer->SetCount(param.cntBomb);
	lifeViewer->SetCount(param.cntLife);
}