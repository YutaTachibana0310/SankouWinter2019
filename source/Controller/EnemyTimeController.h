//=====================================
//
//EnemyTimeController.h
//機能:エネミータイムコントローた
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYTIMECONTROLLER_H_
#define _ENEMYTIMECONTROLLER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyTimeController
{
public:
	static float GetTimeScale();
	static void SetTimeScale(float scale);

	static float GetBulletTimeScale();
	static void  SlowDownBullet(bool enable);

private:
	static float timeScale;
	static bool isSlowDownBullet;
};

#endif