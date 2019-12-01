//=====================================
//
//DemoEnemyActor.h
//�@�\:�ł��G�l�~�[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEMOENEMYACTOR_H_
#define _DEMOENEMYACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"
#include "BaseEnemy.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BoxCollider3D;

/**************************************
�N���X��`
***************************************/
class DemoEnemyActor : public BaseEnemy, public ColliderObserver
{
public:
	DemoEnemyActor();
	~DemoEnemyActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	virtual void OnColliderHit(ColliderObserver * other) override;

private:

};

#endif