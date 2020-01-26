//=====================================
//
// FleetWait.cpp
// 機能:フリートエネミー待機ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetWait.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/
static float Duration = 30.0f;

/**************************************
入場処理
***************************************/
void FleetEnemy::FleetWait::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;
}

/**************************************
更新処理
***************************************/
FleetEnemy::FleetState FleetEnemy::FleetWait::OnUpdate(FleetEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		FleetState next = entity.cntAttack != 0 ? InsanityState : AttackState;
		entity.ChangeState(next);
	}

	return FleetState::WaitState;
}
