//=====================================
//
//DemoAttack.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEMOATTACK_H_
#define _DEMOATTACK_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class DemoEnemyActor::DemoAttack : public BaseState<DemoEnemyActor, DemoEnemyActor::DemoState>
{
	virtual void OnStart(DemoEnemyActor & entity) override;
	virtual DemoState OnUpdate(DemoEnemyActor & entity) override;
};

#endif