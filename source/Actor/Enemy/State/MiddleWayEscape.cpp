//=====================================
//
// MiddleWayEscape.cpp
// 機能:中型ウェイエネミー逃走ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "MiddleWayEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

/**************************************
グローバル変数
***************************************/
static const float Duration = 90.0f;

/**************************************
入場処理
***************************************/
void MiddleWayEnemy::MiddleWayEscape::OnStart(MiddleWayEnemy & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 TargetPosition = entity.transform->GetPosition() + Vector3::Forward * 60.0f;
	EnemyTween::Move(entity, TargetPosition, Duration, EaseType::InSine);
}

/**************************************
更新処理
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
