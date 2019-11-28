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

/**************************************
�N���X��`
***************************************/
class PlayerTurretActor : public GameObject
{
public:
	PlayerTurretActor();
	~PlayerTurretActor();

	void Init(Transform* parent);
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3 GetShotPosition() const;

private:
	MeshContainer * mesh;
	Transform *parent;

	static const D3DXVECTOR3 OffsetShot;
};

#endif