//=====================================
//
// BaseMiddleEnemy.h
// �@�\:���^�G�l�~�[���N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEMIDDLENEMY_H_
#define _BASEMIDDLENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseMiddleEnemy : public BaseEnemy
{
public:
	void Explode();
	EnemyType GetType();
};

#endif