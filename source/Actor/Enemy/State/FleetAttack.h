//=====================================
//
// FleetAttack.h
// �@�\:�t���[�g�G�l�~�[�U���X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETATTACK_H_
#define _FLEETATTACK_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy::FleetAttack : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif