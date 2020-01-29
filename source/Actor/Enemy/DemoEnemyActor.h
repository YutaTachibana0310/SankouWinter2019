//=====================================
//
//DemoEnemyActor.h
//�@�\:�ł��G�l�~�[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOENEMYACTOR_H_
#define _DEMOENEMYACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "Base/BaseMiddleEnemy.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BoxCollider3D;
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor : public BaseMiddleEnemy
{
public:
	DemoEnemyActor(EnemyEventHandler* handler);
	~DemoEnemyActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	enum DemoState
	{
		InitState,
		AttackState,
		EscapeState,
		WaitState,
		MaxState
	};

private:
	std::shared_ptr<Transform> shotTransformLeft;
	std::shared_ptr<Transform> shotTransformRight;

	float cntFrame;
	int cntAttack;

	std::vector<BaseState<DemoEnemyActor, DemoState>*> fsm;
	DemoState state;

	BaseEmitter *trailEmitterR;
	BaseEmitter *trailEmitterL;

	class DemoInit;
	class DemoAttack;
	class DemoWait;
	class DemoEscape;

	void ChangeState(int next);
};

#endif