//=====================================
//
//DemoInit.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "DemoInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

static const float Duration = 60;
/**************************************
入場処理
***************************************/
void DemoEnemyActor::DemoInit::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0;
	entity.cntAttack = 0;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Back * 30.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutSine);
}

/**************************************
更新処理
***************************************/
DemoEnemyActor::DemoState DemoEnemyActor::DemoInit::OnUpdate(DemoEnemyActor & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.ChangeState(DemoState::AttackState);
	}

	return DemoState::InitState;
}
