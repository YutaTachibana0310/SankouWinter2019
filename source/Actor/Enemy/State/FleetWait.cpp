//=====================================
//
// FleetWait.cpp
// �@�\:�t���[�g�G�l�~�[�ҋ@�X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FleetWait.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static float Duration = 30.0f;

/**************************************
���ꏈ��
***************************************/
void FleetEnemy::FleetWait::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;
}

/**************************************
�X�V����
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
