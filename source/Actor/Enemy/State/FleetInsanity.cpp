//=====================================
//
// FleetInsanity.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "FleetInsanity.h"
#include "../../../Controller/EnemyTimeController.h"
#include "../../../Handler/EnemyEventHandler.h"
#include "../../../Controller/EnemyBulletConfig.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void FleetEnemy::FleetInsanity::OnStart(FleetEnemy & entity)
{
	entity.cntFrame = 0.0f;
	entity.cntAttack = 0;
}

/**************************************
更新処理
***************************************/
FleetEnemy::FleetState FleetEnemy::FleetInsanity::OnUpdate(FleetEnemy & entity)
{
	entity.cntFrame += EnemyTimeController::GetTimeScale();

	const float Interval = 5.0f;
	if (entity.cntFrame >= Interval * entity.cntAttack)
	{
		entity.LookAtPlayer(*entity.shotTransform);

		const float BulletSpeed = 0.25f;
		const float SpeedRange = 0.2f;
		
		for (int i = 0; i < 3; i++)
		{
			const float Speed = Math::RandomRange(BulletSpeed - SpeedRange, BulletSpeed + SpeedRange);
			entity.handle->SetStrewBullet(*entity.shotTransform, EnemyBulletConfig::BlueLarge, Speed, 30.0f);
		}

		++entity.cntAttack;
	}

	const int AttackMax = 60;
	if (entity.cntAttack > AttackMax)
	{
		entity.ChangeState(EscapeState);
	}

	return InsanityState;
}
