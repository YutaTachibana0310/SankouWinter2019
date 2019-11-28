//=====================================
//
//PlayerBulletActor.h
//�@�\:�v���C���[�o���b�g�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERULLETACTOR_H_
#define _PLAYERULLETACTOR_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class PlayerBulletActor : public GameObject
{
public:
	PlayerBulletActor();
	~PlayerBulletActor();

	void Init(const D3DXVECTOR3& position);
	void Uninit();
	void Update();
	void Draw();

	static const float SpeedMove;

private:
	BoardPolygon * polygon;

};
#endif