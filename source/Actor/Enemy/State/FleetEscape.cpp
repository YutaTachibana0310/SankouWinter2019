//=====================================
//
// FleetEscape.cpp
// 機能:フリートエネミー逃走ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetEscape.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../System/EnemyTween.h"

/**************************************
グローバル変数
***************************************/
static const float Duration = 120.0f;

/**************************************
入場処理
***************************************/
void FleetEnemy::FleetEscape::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 TargetPosition = entity.transform->GetPosition() + Vector3::Forward * 50.0f;
	EnemyTween::Move(entity, TargetPosition, Duration, EaseType::OutSine);
}

/**************************************
更新処理
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
