//=====================================
//
// FleetEscape.h
// �@�\:�t���[�g�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETESCAPE_H_
#define _FLEETESCAPE_H_

#include "../../../../main.h"
#include "../FleetEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy::FleetEscape : public BaseState<FleetEnemy, FleetState>
{
public:
	void OnStart(FleetEnemy& entity);
	FleetState OnUpdate(FleetEnemy& entity);
};

#endif