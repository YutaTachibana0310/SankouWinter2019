//=====================================
//
// MiddleWayAttack.h
// �@�\:���^�E�F�C�G�l�~�[�U���X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEWAYATTACK_H_
#define _MIDDLEWAYATTACK_H_

#include "../../../../main.h"
#include "../MiddleWayEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MiddleWayEnemy::MiddleWayAttack : public MiddleWayEnemy::MiddleWayState
{
public:
	void OnStart(MiddleWayEnemy& entity);
	State OnUpdate(MiddleWayEnemy& entity);
};

#endif