//=====================================
//
// FleetInit.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/
static const float Duration = 45.0f;

/**************************************
入場処理
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
更新処理
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
