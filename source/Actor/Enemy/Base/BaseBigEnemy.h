//=====================================
//
// BaseBigEnemy.h
// �@�\:��^�G�l�~�[���N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEBIGENEMY_H_
#define _BASEBIGENEMY_H_

#include "../../../../main.h"
#include "BaseEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseBigEnemy : public BaseEnemy
{
public:
	BaseBigEnemy(EnemyEventHandler* handler);

	virtual void Uninit();

	void Explode();
	EnemyType GetType();

	virtual bool IsDestroied() override;

protected:
	bool isDestroied;
};

#endif