//=====================================
//
// FleetEscape.cpp
// �@�\:�t���[�g�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FleetEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../System/EnemyTween.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float Duration = 120.0f;

/**************************************
���ꏈ��
***************************************/
void FleetEnemy::FleetEscape::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 TargetPosition = entity.transform->GetPosition() + Vector3::Forward * 50.0f;
	EnemyTween::Move(entity, TargetPosition, Duration, EaseType::OutSine);
}

/**************************************
�X�V����
***************************************/
FleetEnemy::FleetState FleetEnemy::FleetEscape::OnUpdate(FleetEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.Uninit();
	}

	return FleetState::EscapeState;
}
