//=====================================
//
//SnipeAttack.h
//�@�\:�X�i�C�v�G�l�~�[�U���X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNIPEATTACK_H_
#define _SNIPEATTACK_H_

#include "../../../../main.h"
#include "../SnipeEnemyActor.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SnipeEnemyActor::SnipeAttack : public BaseState<SnipeEnemyActor, SnipeState>
{
public:
	void OnStart(SnipeEnemyActor& entity);
	SnipeState OnUpdate(SnipeEnemyActor& entity);
};
#endif