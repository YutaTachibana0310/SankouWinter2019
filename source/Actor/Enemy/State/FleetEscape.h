//=====================================
//
// FleetEscape.h
// 機能:フリートエネミー逃走ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETESCAPE_H_
#define _FLEETESCAPE_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy::FleetEscape : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif