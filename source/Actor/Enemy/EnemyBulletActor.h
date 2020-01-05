//=====================================
//
// EnemyBulletActor.h
// 機能:エネミーバレット
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETACTOR_H_
#define _ENEMYBULLETACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
前方宣言
***************************************/
class BoxCollider3D;
class BoardPolygon;

enum EnemyBulletType
{
	RedRotate,
	RedLarge,
	RedSphere,
	RedNeedle,
	BlueRotate,
	BlueLarge,
	BlueSphere,
	BlueNeedle,
};

/**************************************
クラス定義
***************************************/
class EnemyBulletActor : public GameObject, public ColliderObserver
{
public:
	EnemyBulletActor();
	~EnemyBulletActor();

	void Init(const Transform& shotTransform);
	void Uninit();
	void Update();
	void Draw();

	static const D3DXVECTOR3 SizeCollider;

private:
	std::shared_ptr<BoxCollider3D> collider;
	BoardPolygon *polygon;

	void OnColliderHit(ColliderObserver * other) override;
};

#endif