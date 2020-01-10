//=====================================
//
//EnemyTimeController.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyTimeController.h"

/**************************************
staticメンバ
***************************************/
float EnemyTimeController::timeScale = 1.0f;
bool EnemyTimeController::isSlowDownBullet = false;

/**************************************
タイムスケール取得
***************************************/
float EnemyTimeController::GetTimeScale()
{
	return timeScale * FixedTime::GetTimeScale();
}

/**************************************
タイムスケール設定
***************************************/
void EnemyTimeController::SetTimeScale(float scale)
{
	timeScale = scale;
}

/**************************************
バレットのタイムスケール取得
***************************************/
float EnemyTimeController::GetBulletTimeScale()
{
	float bulletTimeScale = isSlowDownBullet ? 0.1f : 1.0f;
	return bulletTimeScale * timeScale * FixedTime::GetTimeScale();
}

/**************************************
バレットのタイムスケール設定処理
***************************************/
void EnemyTimeController::SlowDownBullet(bool enable)
{
	isSlowDownBullet = enable;
}

