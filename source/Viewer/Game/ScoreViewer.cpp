//=====================================
//
// ScoreViewer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ScoreViewer.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Tool/DebugWindow.h"

#include "../../System/GameScore.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ScoreViewer::ScoreViewer()
{
	caption = new TextViewer("BadFennec", 40);
	num = new TextViewer("BadFennec", 80);

	caption->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Right);
	num->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Right);

	caption->SetText("SCORE");
	num->SetText("0");

	caption->UseOutLine(true);
	caption->SetOutlineColor(D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));
	caption->SetOutlineWidth(5);

	caption->SetPosition({1850.0f, 30.0f, 0.0f});
	num->SetPosition({ 1850.0f, 80.0f, 0.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
ScoreViewer::~ScoreViewer()
{
	SAFE_DELETE(caption);
	SAFE_DELETE(num);
}

/**************************************
�X�V����
***************************************/
void ScoreViewer::Update()
{
	SetScore(GameScore::Instance()->Score());
}

/**************************************
�`�揈��
***************************************/
void ScoreViewer::Draw()
{
	caption->Draw();
	num->Draw();
}

/**************************************
�����ݒ菈��
***************************************/
void ScoreViewer::SetScore(int score)
{
	num->SetText(std::to_string(score));
}
