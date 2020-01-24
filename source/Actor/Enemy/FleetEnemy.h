//=====================================
//
// FleetEnemy.h
// �@�\:��^�̓G�l�~�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FLEETENEMY_H_
#define _FLEETENEMY_H_

#include "../../../main.h"
#include "Base/BaseBigEnemy.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FleetEnemy : public BaseBigEnemy
{
public:
	FleetEnemy(EnemyEventHandler* handler);
	~FleetEnemy();

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	void ChangeState(int next) {}
};

#endif