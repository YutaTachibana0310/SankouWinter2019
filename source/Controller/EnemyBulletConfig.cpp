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
const D3DXVECTOR2 EnemyBulletConfig::SizePolygon = { 2.0f, 2.0f };
const D3DXVECTOR2 EnemyBulletConfig::SplitTexture = { 8.0f, 8.0f };

/**************************************
テクスチャ通し番号取得
***************************************/
int EnemyBulletConfig::GetTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}

/**************************************
ブルームテクスチャ通し番号取得
***************************************/
int EnemyBulletConfig::GetBloomTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2 + PeriodAnimation;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}
