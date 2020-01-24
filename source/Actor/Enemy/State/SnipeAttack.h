//=====================================
//
//SnipeAttack.h
//機能:スナイプエネミー攻撃ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNIPEATTACK_H_
#define _SNIPEATTACK_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SnipeEnemyActor::SnipeAttack : public BaseState<SnipeEnemyActor, SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};
#endif