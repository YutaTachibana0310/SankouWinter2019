//=====================================
//
//BaseSmallEnemy.h
//�@�\:���^�G�l�~�[���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASESMALLENEMY_H_
#define _BASESMALLENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseSmallEnemy : public BaseEnemy
{
	using BaseEnemy::BaseEnemy;
public:
	void Explode();

	EnemyType GetType();
};

#endif