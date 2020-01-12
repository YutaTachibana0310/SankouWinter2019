//=====================================
//
//PlayerController.h
//�@�\:�v���C���[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class PlayerActor;
class PlayerBulletController;

/**************************************
�N���X��`
***************************************/
class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void Update();
	void Draw();
	void DrawBullet();

private:
	PlayerActor * player;
	PlayerBulletController *bulletController;

	float cntEnergy;

	static const float MaxEnergy;

	void InputEnemyBulletSlowDown();
};
#endif