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
#include <list>

/**************************************
�O���錾
***************************************/
class BaseEnemy;
class EnemyBulletController;

#undef small
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
	std::list<BaseEnemy*> enemyContainer;

	EnemyBulletController *bulletController;
};

#endif