//=====================================
//
//DemoAttack.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOATTACK_H_
#define _DEMOATTACK_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor::DemoAttack : public BaseState<DemoEnemyActor, DemoEnemyActor::DemoState>
{
	virtual void OnStart(DemoEnemyActor & entity) override;
	virtual DemoState OnUpdate(DemoEnemyActor & entity) override;
};

#endif