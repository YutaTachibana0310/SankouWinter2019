//=====================================
//
// MiddleWayInit.h
// �@�\:���^�E�F�C�G�l�~�[�����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MIDDLEWAYINIT_H_
#define _MIDDLEWAYINIT_H_

#include "../../../../main.h"
#include "../MiddleWayEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MiddleWayEnemy::MiddleWayInit : public MiddleWayEnemy::MiddleWayState
{
public:
	void OnStart(MiddleWayEnemy& entity);
	State OnUpdate(MiddleWayEnemy& entity);
};

#endif