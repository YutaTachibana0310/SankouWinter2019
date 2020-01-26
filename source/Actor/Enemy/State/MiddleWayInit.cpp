//=====================================
//
// MiddleWayInit.cpp
// 機能:中型ウェイエネミー初期ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "MiddleWayInit.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

/**************************************
グローバル変数
***************************************/
static const float Duration = 60.0f;

/**************************************
入場処理
***************************************/
void MiddleWayEnemy::MiddleWayInit::OnStart(MiddleWayEnemy & entity)
{
	entity.cntFrame = 0.0f;
	
	D3DXVECTOR3 targetPosition = entity.transform->GetPosition();
	const float Offset = targetPosition.y > 0.0f ? -40.0f : 40.0f;
	targetPosition.y += Offset;

	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutCubic);
}

/**************************************
更新処理
***************************************/
MiddleWayEnemy::State MiddleWayEnemy::MiddleWayInit::OnUpdate(MiddleWayEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();
	if (entity.cntFrame >= Duration)
	{
		entity.ChangeState(AttackState);
	}

	return State::InitState;
}
