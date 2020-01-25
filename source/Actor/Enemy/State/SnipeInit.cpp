//=====================================
//
//SnipeInit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnipeInit.h"
#include "../../../System/EnemyTween.h"
#include "../../../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static const float Duration = 60;

/**************************************
���ꏈ��
***************************************/
void SnipeEnemyActor::SnipeInit::OnStart(SnipeEnemyActor & entity)
{
	entity.cntFrame = 0.0f;

	const D3DXVECTOR3 targetPosition = entity.transform->GetPosition() + Vector3::Back * 40.0f;
	EnemyTween::Move(entity, targetPosition, Duration, EaseType::OutSine);
}

/**************************************
�X�V����
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
