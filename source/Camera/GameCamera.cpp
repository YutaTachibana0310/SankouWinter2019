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
/**************************************
�R���X�g���N�^
***************************************/
GameCamera::GameCamera()
{;
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
		if (cntFocus > 60)
		{
			Tween::Move(*this, InitPosition, 10.0f, EaseType::OutCubic, true);
			Tween::To(tweenViewAngle, D3DXToRadian(60.0f), 10.0f, EaseType::OutCubic, true);
			FixedTime::SetTimeScale(1.0f);
			inFocus = false;
		}
	}
	
	viewAngle = *tweenViewAngle;

	Camera::Update();
}

/**************************************
�w��̈ʒu�𒍎�������
***************************************/
void GameCamera::Focus(const D3DXVECTOR3 & position)
{
	D3DXVECTOR3 target = position;
	target.x = 50.0f;

	Tween::Move(*this, target, 10.0f, EaseType::OutCubic, true);
	Tween::To(tweenViewAngle, D3DXToRadian(50.0f), 10.0f, EaseType::OutCubic, true);
	FixedTime::SetTimeScale(0.05f);

	cntFocus = 0;
	inFocus = true;
}
