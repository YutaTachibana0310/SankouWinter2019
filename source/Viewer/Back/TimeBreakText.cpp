//=====================================
//
//TimeBreakText.cpp
//�@�\:TIME BREAK�e�L�X�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TimeBreakText.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Resource/ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const D3DXVECTOR3 TimeBreakText::InitPositionUpper = { SCREEN_WIDTH * 1.5f, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::InitPositionLower = { SCREEN_WIDTH * -0.5f, 830.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::PositionUpper = { SCREEN_CENTER_X, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::PositionLower = { SCREEN_CENTER_X, 830.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::LastPositionUpper = { SCREEN_WIDTH * -0.5f, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::LastPositionLower = { SCREEN_WIDTH * 1.5f, 830.0f, 0.0f };

static const char* TexturePath[] = {
	"data/TEXTURE/Viewer/TimeBreak.png",
	"data/TEXTURE/Viewer/PowerUp.png"
};

/**************************************
�R���X�g���N�^
***************************************/
TimeBreakText::TimeBreakText() :
	inPlaying(false)
{
	upper = new Polygon2D();
	lower = new Polygon2D();

	for (int i = 0; i < TypeMax; i++)
	{
		ResourceManager::Instance()->LoadTexture(TexturePath[i]);
	}

	upper->SetPosition(InitPositionUpper);
	lower->SetPosition(InitPositionLower);

	upper->SetSize({ 960.0f, 270.0f });
	lower->SetSize({ 960.0f, 270.0f });

	upper->SetUV(0.0f, 0.0f, 1.0f, 0.5f);
	lower->SetUV(0.0f, 0.5f, 1.0f, 0.5f);
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
void TimeBreakText::Set(Type type)
{
	if (inPlaying)
		return;

	upper->LoadTexture(TexturePath[type]);
	lower->LoadTexture(TexturePath[type]);

	upper->SetPosition(InitPositionUpper);
	lower->SetPosition(InitPositionLower);

	auto callback = std::bind(&TimeBreakText::OnFinishIn, this);
	Tween::Move(*upper, PositionUpper, 60.0f, EaseType::OutCubic, true);
	Tween::Move(*lower, PositionLower, 60.0f, EaseType::OutCubic, true, callback);
}

/**************************************
�e�L�X�g�C���I���R�[���o�b�N
***************************************/
void TimeBreakText::OnFinishIn()
{
	auto callback = std::bind(&TimeBreakText::OnFinishOut, this);

	TaskManager::Instance()->CreateDelayedTask(30.0f, true, [=]()
	{
		Tween::Move(*upper, LastPositionUpper, 60.0f, EaseType::InCubic, true);
		Tween::Move(*lower, LastPositionLower, 60.0f, EaseType::InCubic, true, callback);
	});
}

/**************************************
�e�L�X�g�A�E�g�I���R�[���o�b�N
***************************************/
void TimeBreakText::OnFinishOut()
{
	inPlaying = false;
}
