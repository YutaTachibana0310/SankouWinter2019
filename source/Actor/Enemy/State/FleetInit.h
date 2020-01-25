//=====================================
//
// FleetInit.h
// 機能:フリーとエネミー初期ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETINIT_H_
#define _FLEETINIT_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy::FleetInit : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif