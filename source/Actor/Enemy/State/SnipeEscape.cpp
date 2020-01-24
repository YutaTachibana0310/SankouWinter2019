//=====================================
//
//SnipeEscape.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnipeEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

static const float Duration = 90.0f;

/**************************************
���ꏈ��
***************************************/
void SnipeEnemyActor::SnipeEscape::OnStart(SnipeEnemyActor & entity)
{
	entity.cntFrame = 0.0f;
	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() - entity.transform->Forward() * 80.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::InCubic);
}

/**************************************
�X�V����
***************************************/
SnipeEnemyActor::SnipeState SnipeEnemyActor::SnipeEscape::OnUpdate(SnipeEnemyActor & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.Uninit();
	}

	return SnipeState::AttackState;
}
