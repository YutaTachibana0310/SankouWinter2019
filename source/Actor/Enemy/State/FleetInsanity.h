//=====================================
//
// FleetInsanity.h
// �@�\:�t���[�g�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETINSANITY_H_
#define _FLEETINSANITY_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy::FleetInsanity : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif