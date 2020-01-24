//=====================================
//
//DemoEscape.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "DemoEscape.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

static const float Duration = 90.0f;

/**************************************
入場処理
***************************************/
void DemoEnemyActor::DemoEscape::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Forward * 50.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::InSine);
}

/**************************************
更新処理
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
