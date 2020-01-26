//=====================================
//
// MiddleWayAttack.h
// 機能:中型ウェイエネミー攻撃ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDDLEWAYATTACK_H_
#define _MIDDLEWAYATTACK_H_

#include "../../../../main.h"
#include "../MiddleWayEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MiddleWayEnemy::MiddleWayAttack : public MiddleWayEnemy::MiddleWayState
{
public:
	void OnStart(MiddleWayEnemy& entity);
	State OnUpdate(MiddleWayEnemy& entity);
};

#endif