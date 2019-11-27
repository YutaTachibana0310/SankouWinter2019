//=====================================
//
//PlayerActor.h
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;

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

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;

private:
	MeshContainer * mesh;

	void Move(const D3DXVECTOR3& dir);
};

#endif