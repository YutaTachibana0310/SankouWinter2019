//=====================================
//
//BaseEnemy.h
//機能:エネミー基底クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEENEMY_H_
#define _BASEENEMY_H_

#include "../../../../main.h"
#include "../../../../Framework/Collider/ColliderObserver.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class BoxCollider3D;
class MeshContainer;
class EnemyEventHandler;

/**************************************
クラス定義
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

	BaseEnemy(EnemyEventHandler* handle);
	virtual ~BaseEnemy();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetCollider(bool state);

	virtual void Explode() = 0;

	virtual EnemyType GetType() = 0;

	virtual bool IsDestroied();

	virtual void ChangeState(int next) = 0;

	virtual void LookAtPlayer(Transform& transform);

protected:
	float hp;
	std::vector<std::shared_ptr<BoxCollider3D>> colliders;
	MeshContainer *mesh;
	
	EnemyEventHandler *handle;

	virtual void OnColliderHit(ColliderObserver * other) override;
};
#endif