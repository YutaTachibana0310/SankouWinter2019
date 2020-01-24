//=====================================
//
// FleetEnemy.h
// 機能:大型艦エネミー
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FLEETENEMY_H_
#define _FLEETENEMY_H_

#include "../../../main.h"
#include "Base/BaseBigEnemy.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FleetEnemy : public BaseBigEnemy
{
public:
	FleetEnemy(EnemyEventHandler* handler);
	~FleetEnemy();

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	void ChangeState(int next) {}
};

#endif