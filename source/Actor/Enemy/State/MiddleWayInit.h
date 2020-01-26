//=====================================
//
// MiddleWayInit.h
// 機能:中型ウェイエネミー初期ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDDLEWAYINIT_H_
#define _MIDDLEWAYINIT_H_

#include "../../../../main.h"
#include "../MiddleWayEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MiddleWayEnemy::MiddleWayInit : public MiddleWayEnemy::MiddleWayState
{
public:
	void OnStart(MiddleWayEnemy& entity);
	State OnUpdate(MiddleWayEnemy& entity);
};

#endif