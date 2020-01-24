//=====================================
//
//SnipeEscape.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnipeEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

static const float Duration = 90.0f;

/**************************************
入場処理
***************************************/
void SnipeEnemyActor::SnipeEscape::OnStart(SnipeEnemyActor & entity)
{
	entity.cntFrame = 0.0f;
	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() - entity.transform->Forward() * 80.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::InCubic);
}

/**************************************
更新処理
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
