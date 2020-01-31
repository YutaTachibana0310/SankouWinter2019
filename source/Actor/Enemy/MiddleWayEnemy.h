//=====================================
//
// MiddleWayEnemy.h
// �@�\:���^�E�F�C�G�l�~�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEWAYENEMY_H_
#define _MIDDLEWAYENEMY_H_

#include "../../../main.h"
#include "Base/BaseMiddleEnemy.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class MiddleWayEnemy : public BaseMiddleEnemy
{
public:
	MiddleWayEnemy(EnemyEventHandler *handle);
	~MiddleWayEnemy();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	enum State
	{
		InitState,
		AttackState,
		WaitState,
		EscapeState,
		StateMax
	};
	using MiddleWayState = BaseState<MiddleWayEnemy, State>;

private:
	std::shared_ptr<Transform> shotTransform;

	float cntFrame;
	int cntAttack;

	bool enableAttack;

	std::vector<MiddleWayState*> fsm;
	State state;

	BaseEmitter *trailEmitterR;
	BaseEmitter *trailEmitterL;

	class MiddleWayInit;
	class MiddleWayAttack;
	class MiddleWayWait;
	class MiddleWayEscape;

	void ChangeState(int next);
};

#endif