//=====================================
//
// MiddleWayInit.cpp
// �@�\:���^�E�F�C�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MiddleWayInit.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../System/EnemyTween.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float Duration = 60.0f;

/**************************************
���ꏈ��
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
�X�V����
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
