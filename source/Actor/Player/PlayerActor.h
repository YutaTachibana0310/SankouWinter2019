//=====================================
//
//PlayerActor.h
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

#include <vector>
#include <functional>

/**************************************
前方宣言
***************************************/
class MeshContainer;
class PlayerTurretActor;
class PlayerTurretRoot;
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class PlayerActor : public GameObject, public ColliderObserver
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	std::function<void(const D3DXVECTOR3)> onFireBullet;
	std::function<void(ColliderObserver* other)> onColliderHit;

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;
	static const float MaxAngle;

private:
	MeshContainer * mesh;

	PlayerTurretRoot *turretRoot;
	std::vector<PlayerTurretActor*> turretContainer;

	std::shared_ptr<BoxCollider3D> collider;

	float cntShotFrame;

	bool enableShot;
	bool enableMove;

	void _Move(const D3DXVECTOR3& dir);
	void _Rotate(float dir);
	void _Shot();

	virtual void OnColliderHit(ColliderObserver * other) override;
	virtual void OnFinishInitMove();
};

#endif