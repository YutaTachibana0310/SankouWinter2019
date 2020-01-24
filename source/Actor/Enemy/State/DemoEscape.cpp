//=====================================
//
//DemoEscape.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoEscape.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

static const float Duration = 90.0f;

/**************************************
���ꏈ��
***************************************/
void DemoEnemyActor::DemoEscape::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Forward * 50.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::InSine);
}

/**************************************
�X�V����
***************************************/
DemoEnemyActor::DemoState DemoEnemyActor::DemoEscape::OnUpdate(DemoEnemyActor & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.Uninit();
	}

	return EscapeState;
}
