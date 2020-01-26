//=====================================
//
//SnipeAttack.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnipeAttack.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Controller/EnemyBulletConfig.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void SnipeEnemyActor::SnipeAttack::OnStart(SnipeEnemyActor & entity)
{
	entity.cntFrame = 0.0f;
	entity.cntAttack = 0;
}

/**************************************
�X�V����
***************************************/
SnipeEnemyActor::SnipeState SnipeEnemyActor::SnipeAttack::OnUpdate(SnipeEnemyActor & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	entity.LookAtPlayer(*entity.transform);

	const float Interval = 90.0f;
	if (entity.cntFrame >= Interval)
	{
		const int MaxAttack = 4;
		if (entity.cntAttack < MaxAttack)
		{
			entity.handle->SetBullet(*entity.shotTransform, EnemyBulletConfig::BlueSphere, 0.5f);
			entity.cntFrame -= Interval;
			++entity.cntAttack;
		}
		else
		{
			entity.ChangeState(EscapeState);
		}
	}

	return SnipeState::AttackState;
}
