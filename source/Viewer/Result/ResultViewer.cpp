//=====================================
//
//ResultViewer.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ResultViewer::ResultViewer()
{
	bg = new Polygon2D();
	bg->LoadTexture("data/TEXTURE/Viewer/ResultBG.jpg");
	bg->SetSize({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });
	bg->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
ResultViewer::~ResultViewer()
{
	SAFE_DELETE(bg);
}

/**************************************
�X�V����
***************************************/
void ResultViewer::Update()
{
}

/**************************************
�`�揈��
***************************************/
void ResultViewer::Draw()
{
	bg->Draw();
}
