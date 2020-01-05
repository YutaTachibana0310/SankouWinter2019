//=====================================
//
// EnemyBulletConfig.cpp
// 機能:エネミーバレット設定
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyBulletConfig.h"

/**************************************
グローバル変数
***************************************/
const int EnemyBulletConfig::PeriodAnimation = 4;

/**************************************
テクスチャ通し番号取得
***************************************/
int EnemyBulletConfig::GetTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}
