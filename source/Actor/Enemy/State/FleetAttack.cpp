//=====================================
//
// FleetAttack.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetAttack.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Controller/EnemyBulletConfig.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void FleetEnemy::FleetAttack::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;
}

/**************************************
更新処理
***************************************/
FleetEnemy::FleetState FleetEnemy::FleetAttack::OnUpdate(FleetEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	const float Interval = 60.0f;
	if (entity.cntFrame >= Interval * entity.cntAttack)
	{		
		const int WayCircle = 8;
		const float RangeWay = 360.0f / (WayCircle * 2.5f);
		const int Way = 10;
		const float RotAngle = 360.0f / WayCircle;
		const float BulletSpeed = 0.25f;

		for (int cntWay = 0; cntWay < WayCircle; cntWay++)
		{
			entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::RedRotate, BulletSpeed, Way, RangeWay);
			entity.shotTransform->Rotate(RotAngle, Vector3::Right);
		}

		entity.shotTransform->Rotate(RotAngle / 2.0f, Vector3::Right);

		for (int cntWay = 0; cntWay < WayCircle; cntWay++)
		{
			entity.handle->SetWayBullet(*entity.shotTransform, EnemyBulletConfig::BlueRotate, BulletSpeed, Way, RangeWay);
			entity.shotTransform->Rotate(RotAngle, Vector3::Right);
		}

		++entity.cntAttack;
	}

	const int AttackMax = 10;
	if (entity.cntAttack > AttackMax)
	{
		//entity.ChangeState(WaitState);
	}

	return FleetState::WaitState;
}
