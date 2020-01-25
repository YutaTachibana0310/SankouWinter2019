//=====================================
//
// FleetAttack.h
// 機能:フリートエネミー攻撃ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETATTACK_H_
#define _FLEETATTACK_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy::FleetAttack : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif