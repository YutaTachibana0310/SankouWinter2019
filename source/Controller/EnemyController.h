//=====================================
//
//EnemyController.h
//�@�\:�G�l�~�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYCONTROLLER_H_
#define _ENEMYCONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class BaseEnemy;
class EnemyBulletController;

/**************************************
�N���X��`
***************************************/
class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void Update();
	void Draw();
	void DrawBullet();

private:
	BaseEnemy * enemy;
	EnemyBulletController *bulletController;
};

#endif