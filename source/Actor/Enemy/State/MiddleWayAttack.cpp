//=====================================
//
// MiddleWayAttack.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "MiddleWayAttack.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Controller/EnemyBulletConfig.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void MiddleWayEnemy::MiddleWayAttack::OnStart(MiddleWayEnemy & entity)
{
	entity.cntFrame = 0.0f;
	entity.cntAttack = 0;
}

/**************************************
更新処理
***************************************/
MiddleWayEnemy::State MiddleWayEnemy::MiddleWayAttack::OnUpdate(MiddleWayEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	const float Interval = 20.0f;
	if (entity.cntFrame >= entity.cntAttack * Interval)
	{
		const float WayAngle = 5.0f;

		entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::RedRotate, 0.45f, 3, WayAngle * 2);
		entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::BlueRotate, 0.2f, 2, WayAngle * 6);

		++entity.cntAttack;

		const int AttackMax = 18;
		if (entity.cntAttack > AttackMax)
		{
			entity.ChangeState(EscapeState);
		}
	}

	return State::AttackState;
}
