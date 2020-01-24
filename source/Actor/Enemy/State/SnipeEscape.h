//=====================================
//
//SnipeEscape.h
//機能:スナイプエネミー逃走ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNIPEESCAPE_H_
#define _SNIPEESCAPE_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SnipeEnemyActor::SnipeEscape : public BaseState<SnipeEnemyActor, SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};

#endif