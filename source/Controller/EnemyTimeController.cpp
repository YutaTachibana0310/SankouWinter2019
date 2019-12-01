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

/**************************************
タイムスケール取得
***************************************/
float EnemyTimeController::GetTimeScale()
{
	return timeScale;
}

/**************************************
タイムスケール設定
***************************************/
void EnemyTimeController::SetTimeScale(float scale)
{
	timeScale = scale;
}
