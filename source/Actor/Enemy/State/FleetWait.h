//=====================================
//
// FleetWait.h
// �@�\:�t���[�ƃG�l�~�[�ҋ@�X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETWAIT_H_
#define _FLEETWAIT_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy::FleetWait : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif