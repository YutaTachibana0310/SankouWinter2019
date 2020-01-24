//=====================================
//
//DemoAttack.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "DemoAttack.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Controller/EnemyBulletConfig.h"

/**************************************
���ꏈ��
***************************************/
void DemoEnemyActor::DemoAttack::OnStart(DemoEnemyActor & entity)
{
	const float BulletSpeed = 0.5f;
	const float SpeedOffset = 0.02f;
	const int CountBullet = 10;

	for (int i = 0; i < CountBullet; i++)
	{
		float speed = BulletSpeed + SpeedOffset * i;
		entity.handle->SetBullet(*entity.shotTransformRight, EnemyBulletConfig::BlueNeedle, speed);
		entity.handle->SetBullet(*entity.shotTransformLeft, EnemyBulletConfig::BlueNeedle, speed);
	}

	entity.cntAttack++;
	entity.ChangeState(DemoState::WaitState);
}

/**************************************
�X�V����
***************************************/
DemoEnemyActor::DemoState DemoEnemyActor::DemoAttack::OnUpdate(DemoEnemyActor & entity)
{
	return DemoState();
}
