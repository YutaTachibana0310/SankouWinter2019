//=====================================
//
//BaseEnemy.h
//�@�\:�G�l�~�[���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEENEMY_H_
#define _BASEENEMY_H_

#include "../../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class BoxCollider3D;
class MeshContainer;

/**************************************
�N���X��`
***************************************/
class BaseEnemy : public GameObject
{
	friend class EnemyTween;
public:
	BaseEnemy();
	virtual ~BaseEnemy();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetCollider(bool state);

protected:
	float hp;
	std::vector<std::shared_ptr<BoxCollider3D>> colliders;
	MeshContainer *mesh;
	
};
#endif