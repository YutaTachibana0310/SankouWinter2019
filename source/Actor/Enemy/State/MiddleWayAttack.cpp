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

	const float Interval = 75.0f;
	if (entity.cntFrame >= entity.cntAttack * Interval)
	{
		const float WayAngle = 25.0f;

		entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::RedRotate, 0.3f, 5, WayAngle * 4);
		entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::BlueRotate, 0.25f, 4, WayAngle * 3);

		++entity.cntAttack;

		const int AttackMax = 5;
		if (entity.cntAttack > AttackMax)
		{
			entity.ChangeState(EscapeState);
		}
	}

	return State::AttackState;
}
