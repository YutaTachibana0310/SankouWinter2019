//=====================================
//
// FleetInit.h
// �@�\:�t���[�ƃG�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETINIT_H_
#define _FLEETINIT_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy::FleetInit : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif