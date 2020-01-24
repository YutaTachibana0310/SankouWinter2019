//=====================================
//
//DemoEscape.h
//機能:デモエネミー逃走ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEMOESCAPE_H_
#define _DEMOESCAPE_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class DemoEnemyActor::DemoEscape : public BaseState<DemoEnemyActor, DemoState>
{
public:
	void OnStart(DemoEnemyActor& entity);
	DemoState OnUpdate(DemoEnemyActor& entity);
};

#endif