//=====================================
//
// MiddleWayEscape.h
// 機能:中型ウェイエネミー逃走ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDDLEWAYESCAPE_H_
#define _MIDDLEWAYESCAPE_H_

#include "../../../../main.h"
#include "../MiddleWayEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MiddleWayEnemy::MiddleWayEscape : public MiddleWayEnemy::MiddleWayState
{
public:
	void OnStart(MiddleWayEnemy& entity);
	State OnUpdate(MiddleWayEnemy& entity);
};

#endif