//=====================================
//
//DemoEnemyActor.h
//機能:でもエネミーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEMOENEMYACTOR_H_
#define _DEMOENEMYACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class DemoEnemyActor : public GameObject, public ColliderObserver
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
	MeshContainer * mesh;
	std::shared_ptr<BoxCollider3D> collider;
};

#endif