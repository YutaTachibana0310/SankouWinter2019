//=====================================
//
//SnipeEnemyActor.h
//機能:スナイプエネミーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNIPEENEMYACTOR_H_
#define _SNIPEENEMYACTOR_H_

#include "../../../main.h"
#include "Base\BaseSmallEnemy.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SnipeEnemyActor : public BaseSmallEnemy
{
public:
	SnipeEnemyActor(EnemyEventHandler* handler);
	~SnipeEnemyActor();

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void ChangeState(int next) override;

private:
	float cntFrame;
	int cntAttack;

	bool enableSnipe;

	std::shared_ptr<Transform> shotTransform;

	enum SnipeState
	{
		InitState,
		AttackState,
		EscapeState,
		StateMax
	};

	std::vector<BaseState<SnipeEnemyActor, SnipeState>*> fsm;
	SnipeState state;

	class SnipeInit;
	class SnipeAttack;
	class SnipeEscape;
};

#endif