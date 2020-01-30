//=====================================
//
//PushViewer.cpp
//�@�\:�v�b�V���r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PushViewer.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float DurationFade = 90.0f;

/**************************************
�R���X�g���N�^
***************************************/
PushViewer::PushViewer()
{
	polygon = std::make_shared<Polygon2D>();
	polygon->LoadTexture("data/TEXTURE/Viewer/PushButton.png");
	polygon->SetSize({ 256.0f, 45.0f });
	polygon->SetPosition({ SCREEN_CENTER_X, 600.0f, 0.0f });

	onFinishFadeIn = std::bind(&PushViewer::OnFinishFadeIn, this);
	onFinishFadeOut = std::bind(&PushViewer::OnFinishFadeOut, this);

	Tween::Fade(polygon, 1.0f, 0.0f, DurationFade, EaseType::Linear, true, onFinishFadeOut);
}

/**************************************
�f�X�g���N�^
***************************************/
PushViewer::~PushViewer()
{
	polygon.reset();
}

/**************************************
�`�揈��
***************************************/
void PushViewer::Draw()
{
	polygon->Draw();
}

/**************************************
�t�F�[�h�C���R�[���o�b�N
***************************************/
void PushViewer::OnFinishFadeIn()
{
	Tween::Fade(polygon, 1.0f, 0.0f, DurationFade, EaseType::Linear, true, onFinishFadeOut);
}

/**************************************
�t�F�[�h�A�E�g�R�[���o�b�N
***************************************/
void PushViewer::OnFinishFadeOut()
{
	Tween::Fade(polygon, 0.0f, 1.0f, DurationFade, EaseType::Linear, true, onFinishFadeIn);
}
