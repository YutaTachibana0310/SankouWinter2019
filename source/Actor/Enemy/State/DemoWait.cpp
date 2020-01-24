//=====================================
//
//DemoWait.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "DemoWait.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
入場処理
***************************************/
void DemoEnemyActor::DemoWait::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0;
}

/**************************************
更新処理
***************************************/
DemoEnemyActor::DemoState DemoEnemyActor::DemoWait::OnUpdate(DemoEnemyActor & entity)
{
	const float Duration = 180.0f;

	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		const int MaxAttack = 3;
		int next = entity.cntAttack == MaxAttack ? EscapeState : AttackState;

		entity.ChangeState(next);
	}

	return DemoState::WaitState;
}
