//=====================================
//
// FixedTime.h
// 機能:このシステムの固定時間管理クラス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIEXEDTIME_H_
#define _FIEXEDTIME_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FixedTime
{
	friend class BaseGame;
	friend class SceneManager;
public:
	static inline void SetTimeScale(float scale)
	{
		timeScale = scale;
	}

	static inline float GetTimeScale()
	{
		return timeScale;
	}

private:
	static float timeScale;
};

#endif