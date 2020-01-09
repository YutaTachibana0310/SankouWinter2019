//=====================================
//
// EnemyBulletHandler.h
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETHANDLER_H_
#define _ENEMYBULLETHANDLER_H_

#include "../../main.h"
#include "../Controller/EnemyBulletConfig.h"

/**************************************
�O���錾
***************************************/
class EnemyBulletController;

/**************************************
�N���X��`
***************************************/
class EnemyBulletHandler
{
public:
	EnemyBulletHandler(EnemyBulletController* controller);
	~EnemyBulletHandler();

	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);
	void SetWayBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle);
	void SetCircleBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way);
	void SetStrewBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange);

	void VanishAllBullet();

private:
	EnemyBulletController *controller;
};

#endif