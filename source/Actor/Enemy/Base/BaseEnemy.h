//=====================================
//
//BaseEnemy.h
//�@�\:�G�l�~�[���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEENEMY_H_
#define _BASEENEMY_H_

#include "../../../../main.h"
#include "../../../../Framework/Collider/ColliderObserver.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class BoxCollider3D;
class MeshContainer;
class EnemyHandler;

/**************************************
�N���X��`
***************************************/
class BaseEnemy : public GameObject, public ColliderObserver
{
	friend class EnemyTween;
public:
	enum EnemyType
	{
		Small,
		Middle,
		Big,
		EnemyTypeMax
	};

	BaseEnemy(EnemyHandler* handle);
	virtual ~BaseEnemy();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetCollider(bool state);

	virtual void Explode() = 0;

	virtual EnemyType GetType() = 0;

	virtual bool IsDestroied();

protected:
	float hp;
	std::vector<std::shared_ptr<BoxCollider3D>> colliders;
	MeshContainer *mesh;
	
	EnemyHandler *handle;

	virtual void OnColliderHit(ColliderObserver * other) override;

};
#endif