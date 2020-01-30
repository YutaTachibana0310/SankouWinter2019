//=====================================
//
//TitlePlayerActor.h
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
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class TitlePlayerActor : public GameObject
{
public:
	TitlePlayerActor();
	virtual ~TitlePlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

private:
	MeshContainer * mesh;
	BaseEmitter *trailEmitter;

	float cntShotFrame;

	bool enableShot;
	bool enableMove;

	int currentLevel;
};

#endif