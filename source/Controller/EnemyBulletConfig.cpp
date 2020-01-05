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
const D3DXVECTOR2 EnemyBulletConfig::SizeUV = { 1.0f / EnemyBulletConfig::SplitTexture.x, 1.0f / EnemyBulletConfig::SplitTexture.y };

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

/**************************************
UV座標取得処理
***************************************/
D3DXVECTOR2 EnemyBulletConfig::GetTextureUV(Type type, int indexAnim, bool isBloom)
{
	int index = isBloom ? GetTextureIndex(type, indexAnim) : GetBloomTextureIndex(type, indexAnim);

	int x = index % (int)SplitTexture.x;
	int y = index / (int)SplitTexture.x;

	D3DXVECTOR2 uv = { 0.0f, 0.0f };
	uv.x = x * SizeUV.x;
	uv.y = y * SizeUV.y;

	return uv;
}