//=====================================
//
//DemoWait.h
//�@�\:�f���G�l�~�[�ҋ@�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOWAIT_H_
#define _DEMOWAIT_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../DemoEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor::DemoWait : public BaseState<DemoEnemyActor, DemoState>
{
public:
	void OnStart(DemoEnemyActor& entity);
	DemoState OnUpdate(DemoEnemyActor& entity);
};
#endif