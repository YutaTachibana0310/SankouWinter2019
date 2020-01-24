//=====================================
//
//DemoInit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

static const float Duration = 60;
/**************************************
���ꏈ��
***************************************/
void DemoEnemyActor::DemoInit::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0;
	entity.cntAttack = 0;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Back * 30.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutSine);
}

/**************************************
�X�V����
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
