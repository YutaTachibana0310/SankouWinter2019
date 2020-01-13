//=====================================
//
//GameCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameCamera.h"
#include "../../Framework/Tween/Tween.h"

#include "../../Framework/Tool/DebugWindow.h"

/**************************************
static�����o
***************************************/
const D3DXVECTOR3 GameCamera::InitPosition = { 50.0f, 0.0f, 0.0f };
const float GameCamera::DurationFocusTransition = 20.0f;
const int GameCamera::DurationFocus = 60;

/**************************************
�R���X�g���N�^
***************************************/
GameCamera::GameCamera() :
	callback(nullptr)
{
	transform->SetPosition(InitPosition);
	transform->LookAt(Vector3::Zero);

	tweenViewAngle = std::make_shared<float>();
	*tweenViewAngle = viewAngle;
}

/**************************************
�f�X�g���N�^
***************************************/
GameCamera::~GameCamera()
{
	tweenViewAngle.reset();
}

/**************************************
�X�V����
***************************************/
void GameCamera::Update()
{
	if (inFocus)
	{
		cntFocus++;
		if (cntFocus > DurationFocus)
		{
			Tween::Move(*this, InitPosition, DurationFocusTransition, EaseType::OutCubic, true);
			Tween::To(tweenViewAngle, D3DXToRadian(60.0f), DurationFocusTransition, EaseType::OutCubic, true);
			FixedTime::SetTimeScale(1.0f);
			inFocus = false;

			if (callback != nullptr)
				callback();
		}
	}
	
	viewAngle = *tweenViewAngle;

	Camera::Update();
}

/**************************************
�w��̈ʒu�𒍎�������
***************************************/
void GameCamera::Focus(const D3DXVECTOR3 & position, const std::function<void()>& callback)
{
	if (inFocus)
		return;

	D3DXVECTOR3 target = position;
	target.x = 50.0f;

	Tween::Move(*this, target, DurationFocusTransition, EaseType::OutCubic, true);
	Tween::To(tweenViewAngle, D3DXToRadian(50.0f), DurationFocusTransition, EaseType::OutCubic, true);
	FixedTime::SetTimeScale(0.05f);

	cntFocus = 0;
	inFocus = true;
	this->callback = callback;
}
