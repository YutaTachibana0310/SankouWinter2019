//=====================================
//
// FleetInsanity.h
// 機能:フリートエネミー発狂ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETINSANITY_H_
#define _FLEETINSANITY_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy::FleetInsanity : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif