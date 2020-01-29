//=====================================
//
//PlayerTurretActor.h
//�@�\:�v���C���[�C��A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERTURRETACTOR_H_
#define _PLAYERTURRETACTOR_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class PlayerTurretActor : public GameObject
{
public:
	PlayerTurretActor();
	~PlayerTurretActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3 GetShotPosition() const;

private:
	MeshContainer * mesh;
	BaseEmitter *trailEmitter;

	static const D3DXVECTOR3 OffsetShot;
};

/**************************************
PlayerTurretRoot�N���X
***************************************/
class PlayerTurretRoot : public GameObject
{
	using GameObject::GameObject;

public:
	void Update();
};
#endif