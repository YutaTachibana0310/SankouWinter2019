//=====================================
//
// EnemyHandler.h
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EnemyHandler_H_
#define _EnemyHandler_H_

#include "../../main.h"
#include "../Controller/EnemyBulletConfig.h"

/**************************************
�O���錾
***************************************/
class EnemyBulletController;
class PlayerController;

/**************************************
�N���X��`
***************************************/
class EnemyHandler
{
public:
	EnemyHandler(
		EnemyBulletController* Bulletcontroller,
		PlayerController* playerController);

	~EnemyHandler();

	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);
	void SetWayBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle);
	void SetCircleBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way);
	void SetStrewBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange);

	void VanishAllBullet();

	void GenerateScoreItem(const D3DXVECTOR3& position);

	void AddScore(int point);

	void SlowdownEnemy();

	void FetchSlowdownState();

private:
	EnemyBulletController *bulletController;
	PlayerController *playerController;

	bool inSlowdown;
};

#endif