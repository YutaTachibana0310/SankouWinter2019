//=====================================
//
//PlayerBulletController.h
//�@�\:�v���C���[�o���b�g�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETCONTROLLER_H_
#define _PLAYERBULLETCONTROLLER_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class PlayerBulletActor;

/**************************************
�N���X��`
***************************************/
class PlayerBulletController
{
public:
	PlayerBulletController();
	~PlayerBulletController();

	void Update();
	void Draw();

	void FireBullet(const D3DXVECTOR3& pos);

private:
	std::vector<PlayerBulletActor*> bulletContainer;
};
#endif