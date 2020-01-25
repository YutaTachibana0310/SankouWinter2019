//=====================================
//
// FleetInit.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FleetInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float Duration = 45.0f;

/**************************************
���ꏈ��
***************************************/
void FleetEnemy::FleetInit::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;
	entity.cntAttack = 0;

	D3DXVECTOR3 targetPosition = entity.transform->GetPosition();
	const float OffsetY = targetPosition.y > 0.0f ? -40.0f : 40.0f;
	targetPosition.y += OffsetY;

	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutCubic);
}

/**************************************
�X�V����
***************************************/
FleetEnemy::FleetState FleetEnemy::FleetInit::OnUpdate(FleetEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.ChangeState(WaitState);
	}

	return FleetState();
}
