//=====================================
//
//SnipeInit.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnipeInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/
static const float Duration = 60;

/**************************************
入場処理
***************************************/
void SnipeEnemyActor::SnipeInit::OnStart(SnipeEnemyActor & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Back * 40.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutSine);
}

/**************************************
更新処理
***************************************/
SnipeEnemyActor::SnipeState SnipeEnemyActor::SnipeInit::OnUpdate(SnipeEnemyActor & entity)
{
	entity.LookAtPlayer(*entity.transform);

	entity.cntFrame += EnemyTimeController::GetTimeScale();

	if (entity.cntFrame >= Duration)
	{
		entity.ChangeState(AttackState);
	}

	return SnipeState();
}
