//=====================================
//
//DemoInit.h
//機能:DemoEnemyの初期ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEMOINIT_H_
#define _DEMOINIT_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class DemoEnemyActor::DemoInit : public BaseState<DemoEnemyActor, DemoEnemyActor::DemoState>
{
	void OnStart(DemoEnemyActor& entity);
	DemoEnemyActor::DemoState OnUpdate(DemoEnemyActor& entity);
};

#endif