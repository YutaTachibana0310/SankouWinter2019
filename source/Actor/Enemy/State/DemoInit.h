//=====================================
//
//DemoInit.h
//�@�\:DemoEnemy�̏����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOINIT_H_
#define _DEMOINIT_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor::DemoInit : public BaseState<DemoEnemyActor, DemoEnemyActor::DemoState>
{
	void OnStart(DemoEnemyActor& entity);
	DemoEnemyActor::DemoState OnUpdate(DemoEnemyActor& entity);
};

#endif