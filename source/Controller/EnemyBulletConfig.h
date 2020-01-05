//=====================================
//
// EnemyBulletConfig.h
// 機能:エネミーバレット設定
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCONFIG_H_
#define _ENEMYBULLETCONFIG_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyBulletConfig
{
public:
	//バレットタイプ
	enum Type
	{
		RedRotate,
		RedLarge,
		RedSphere,
		RedNeedle,
		BlueRotate,
		BlueLarge,
		BlueSphere,
		BlueNeedle,
		EnemyBulletMax
	};

	static int GetTextureIndex(Type type, int indexAnim);
	static int GetBloomTextureIndex(Type type, int indexAnim);

private:
	EnemyBulletConfig() {}
	~EnemyBulletConfig() {}

	static const int PeriodAnimation;
};

#endif