//=====================================
//
// MiddleWayEscape.cpp
// �@�\:���^�E�F�C�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MiddleWayEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float Duration = 90.0f;

/**************************************
���ꏈ��
***************************************/
void MiddleWayEnemy::MiddleWayEscape::OnStart(MiddleWayEnemy & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 TargetPosition = entity.transform->GetPosition() + Vector3::Forward * 60.0f;
	EnemyTween::Move(entity, TargetPosition, Duration, EaseType::InSine);
}

/**************************************
�X�V����
***************************************/
MiddleWayEnemy::State MiddleWayEnemy::MiddleWayEscape::OnUpdate(MiddleWayEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.Uninit();
	}

	return State::EscapeState;
}
