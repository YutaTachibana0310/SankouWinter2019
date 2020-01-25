//=====================================
//
// FleetWait.h
// 機能:フリーとエネミー待機ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETWAIT_H_
#define _FLEETWAIT_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy::FleetWait : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif