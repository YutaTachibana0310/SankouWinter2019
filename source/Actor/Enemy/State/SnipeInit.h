//=====================================
//
//SnipeInit.h
//機能:スナイプエネミー初期ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNIPEINIT_H_
#define _SNIPEINIT_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SnipeEnemyActor::SnipeInit : public BaseState<SnipeEnemyActor, SnipeEnemyActor::SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};
#endif