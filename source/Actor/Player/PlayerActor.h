//=====================================
//
//PlayerActor.h
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../../main.h"
#include <vector>
#include <functional>

/**************************************
�O���錾
***************************************/
class MeshContainer;
class PlayerTurretActor;
class PlayerTurretRoot;

/**************************************
�N���X��`
***************************************/
class PlayerActor : public GameObject
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	std::function<void(const D3DXVECTOR3)> onFireBullet;

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;
	static const float MaxAngle;

private:
	MeshContainer * mesh;

	PlayerTurretRoot *turretRoot;
	std::vector<PlayerTurretActor*> turretContainer;

	float cntShotFrame;

	void _Move(const D3DXVECTOR3& dir);
	void _Rotate(float dir);
	void _Shot();
};

#endif