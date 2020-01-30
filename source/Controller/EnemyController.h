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
class GameCamera;
class EnemyEventHandler;
class PlayerController;
class EnemyController;
class EnemyFactory;

/**************************************
�N���X��`
***************************************/
class EnemyController
{
public:
	EnemyController(GameCamera *gameCamera);
	~EnemyController();

	void Init();
	void Update();
	void Draw();
	void DrawBullet();

	void CheckEnemyDestroy();

	void SetEnemyEventHandler(EnemyEventHandler *handler);

private:
	std::list<BaseEnemy*> enemyContainer;

	EnemyBulletController *bulletController;

	GameCamera *gameCamera;

	EnemyEventHandler* enemyEventHandler;

	EnemyFactory *factory;

	bool enableGenerateEnemy;
};

#endif