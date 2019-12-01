//=====================================
//
//BaseEnemy.h
//機能:エネミー基底クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEENEMY_H_
#define _BASEENEMY_H_

#include "../../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class BoxCollider3D;
class MeshContainer;

/**************************************
クラス定義
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