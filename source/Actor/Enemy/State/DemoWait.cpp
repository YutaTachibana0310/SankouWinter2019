//=====================================
//
//DemoWait.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoWait.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
���ꏈ��
***************************************/
void DemoEnemyActor::DemoWait::OnStart(DemoEnemyActor & entity)
{
	entity.cntFrame = 0;
}

/**************************************
�X�V����
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
