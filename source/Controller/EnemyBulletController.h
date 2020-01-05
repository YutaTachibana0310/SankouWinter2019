//=====================================
//
// EnemyBulletController.h
// �@�\:�G�l�~�[�o���b�g�R���g���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETCONTROLLER_H_
#define _ENEMYBULLETCONTROLLER_H_

#include "../../main.h"
#include "EnemyBulletConfig.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class EnemyBulletActor;

/**************************************
�N���X��`
***************************************/
class EnemyBulletController
{
public:
	EnemyBulletController();
	~EnemyBulletController();

	void Update();
	void Draw();
	
	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type);

	static const unsigned MaxBullet;

private:
	std::vector<EnemyBulletActor*> bulletContainer;
	unsigned cntBullet;
};

#endif