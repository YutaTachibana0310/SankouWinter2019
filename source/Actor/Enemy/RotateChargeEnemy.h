//=====================================
//
//RotateChargeEnemy.h
//�@�\:��]���ēːi����G�l�~�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ROTATECHARGEENEMYACTOR_H_
#define _ROTATECHARGEENEMYACTOR_H_

#include "../../../main.h"
#include "Base\BaseSmallEnemy.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class RotateChargeEnemy : public BaseSmallEnemy
{
public:
	RotateChargeEnemy(EnemyEventHandler* handler);
	~RotateChargeEnemy();

	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	void ChangeState(int next) {}

	void Explode() override;

private:
	bool enableHoming;
	BaseEmitter *trailEmitter;
};

#endif