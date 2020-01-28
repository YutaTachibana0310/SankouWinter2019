//=====================================
//
// EventHandler.h
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "../../main.h"
#include "../Controller/EnemyBulletConfig.h"

/**************************************
�O���錾
***************************************/
class EnemyBulletController;
class PlayerController;
class BackViewer;

/**************************************
�N���X��`
***************************************/
class EnemyEventHandler
{
public:
	EnemyEventHandler();

	~EnemyEventHandler();

	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);
	void SetWayBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle);
	void SetCircleBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, int way);
	void SetStrewBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange);

	void VanishAllBullet();

	void GenerateScoreItem(const D3DXVECTOR3& position);

	void AddScore(int point);

	void SlowdownEnemy();

	void FetchSlowdownState();

	D3DXVECTOR3 GetPlayerPosition() const;

	void GeneratePowerupItem(const D3DXVECTOR3& position);

	void GiveEnemyBulletController(EnemyBulletController *controller);
	void GivePlayerController(PlayerController *controller);
	void GiveBackViewer(BackViewer *viewer);

private:
	EnemyBulletController *bulletController;
	PlayerController *playerController;
	BackViewer *backViewer;

	bool inSlowdown;
};

#endif