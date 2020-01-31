//=====================================
//
//BackViewer.cpp
//�@�\:�w�iUI�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Tween/Tween.h"
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
	greenBG = std::make_shared<Polygon2D>();
	
	greenBG->SetSize({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f });
	greenBG->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	greenBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	greenBG->LoadTexture("data/TEXTURE/Viewer/GreenBG.png");
}

/**************************************
�f�X�g���N�^
***************************************/
BackViewer::~BackViewer()
{
	SAFE_DELETE(timeBreak);
	greenBG.reset();
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

	greenBG->Draw();

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
	timeBreak->Set(TimeBreakText::TimeBreak);
}

/**************************************
PowerUp�Đ�����
***************************************/
void BackViewer::PlayPowerUp()
{
	timeBreak->Set(TimeBreakText::PowerUp);
}

/*************************************
�Δw�i�Z�b�g
***************************************/
void BackViewer::SetGreenBG(bool state)
{
	if (state == greenBGstate)
		return;

	float alpha = state ? 1.0f : 0.0f;
	float current = greenBG->GetDiffuse().a;

	Tween::Fade(greenBG, current, alpha, 20.0f, EaseType::Linear, false);
	greenBGstate = state;
}
