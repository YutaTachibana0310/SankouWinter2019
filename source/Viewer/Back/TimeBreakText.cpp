//=====================================
//
//TimeBreakText.cpp
//�@�\:TIME BREAK�e�L�X�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TimeBreakText.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 TimeBreakText::InitPositionUpper = { SCREEN_WIDTH * 1.5f, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::InitPositionLower = { SCREEN_WIDTH * -0.5f, 720.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::PositionUpper = { SCREEN_CENTER_X, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::PositionLower = { SCREEN_CENTER_X, 720.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::LastPositionUpper = { SCREEN_WIDTH * -0.5f, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::LastPositionLower = { SCREEN_WIDTH * 1.5f, 720.0f, 0.0f };

/**************************************
�R���X�g���N�^
***************************************/
TimeBreakText::TimeBreakText()
{
	upper = new Polygon2D();
	lower = new Polygon2D();

	upper->LoadTexture("data/TEXTURE/TimeBreak.png");
	lower->LoadTexture("data/TEXTURE/TimeBreak.png");

	upper->SetActive(false);
	lower->SetActive(false);
}

/**************************************
�f�X�g���N�^
***************************************/
TimeBreakText::~TimeBreakText()
{
	SAFE_DELETE(upper);
	SAFE_DELETE(lower);
}

/**************************************
�`�揈��
***************************************/
void TimeBreakText::Draw()
{
	upper->Draw();
	lower->Draw();
}

/**************************************
�Z�b�g����
***************************************/
void TimeBreakText::Set()
{

}

/**************************************
�e�L�X�g�C���I���R�[���o�b�N
***************************************/
void TimeBreakText::OnFinishIn()
{
}

/**************************************
�e�L�X�g�A�E�g�I���R�[���o�b�N
***************************************/
void TimeBreakText::OnFinishOut()
{
}
