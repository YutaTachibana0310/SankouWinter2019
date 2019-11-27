//=====================================
//
//�J�������s�ړ��v���O�C������[CameraTranslationPluign.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "CameraTranslationPlugin.h"
#include "../Math/Easing.h"

/**************************************
����������
***************************************/
void CameraTranslationPlugin::Init()
{
	cntFrame = 0;
	durationMove = 0;
	targetPosition = Vector3::Zero;
	state = Idle;
	callback = nullptr;
}

/**************************************
�X�V����
***************************************/
void CameraTranslationPlugin::Update()
{
	if (cntFrame >= durationMove || state == Idle)
		return;

	cntFrame++;

	if (cntFrame == durationMove && callback != nullptr)
		callback();
}

/**************************************
�K�p����
***************************************/
void CameraTranslationPlugin::Apply(Transform& work)
{
	if (state == Idle)
		return;

	float t = (float)cntFrame / durationMove;

	if (state == RestoreBase)
		t = 1.0f - t;

	//�C�[�W���O�ɂ��ړ��l���v�Z
	EaseType type = state == MoveTowards ? EaseType::OutCubic : EaseType::InCubic;
	D3DXVECTOR3 offsetPosition = Easing::EaseValue(t, Vector3::Zero, targetPosition - work.GetPosition(), type);

	work.Move(offsetPosition);
}

/**************************************
���s�ړ��Z�b�g����
***************************************/
void CameraTranslationPlugin::Move(const D3DXVECTOR3 & position, int duration, std::function<void(void)> callback)
{
	targetPosition = position;
	cntFrame = 0;
	durationMove = duration;
	state = MoveTowards;

	this->callback = callback;
}

/**************************************
���s�ړ���������
***************************************/
void CameraTranslationPlugin::Restore(int duration, std::function<void(void)> callback)
{
	cntFrame = 0;
	durationMove = duration;
	state = RestoreBase;
	
	this->callback = callback;
}
