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
#include "../../../Framework/Pattern/BaseState.h"

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

	void ChangeState(int next);

private:
	enum FleetState
	{
		InitState,
		WaitState,
		AttackState,
		InsanityState,
		EscapeState,
		StateMax
	};

	std::vector<BaseState<FleetEnemy, FleetState>*> fsm;
	FleetState state;

	float cntFrame;
	int cntAttack;

	std::shared_ptr<Transform> shotTransform;

	class FleetInit;
	class FleetWait;
	class FleetAttack;
	class FleetInsanity;
	class FleetEscape;
};

#endif