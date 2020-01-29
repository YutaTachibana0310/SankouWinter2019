//=====================================
//
//PlayerActor.h
//�@�\:�v���C���[�A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

#include <vector>
#include <functional>

/**************************************
�O���錾
***************************************/
class MeshContainer;
class PlayerTurretActor;
class PlayerTurretRoot;
class BoxCollider3D;
class PlayerColliderViewer;
class BaseEmitter;

/**************************************
�N���X��`
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
	virtual void DrawCollider();
	
	virtual void PowerUp();

	std::function<void(const D3DXVECTOR3, bool, int)> onFireBullet;
	std::function<void(ColliderObserver* other)> onColliderHit;
	std::function<void(bool slowDown)> onSlowdownEnemyBullet;
	std::function<void()> onFireBomber;

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;
	static const D3DXVECTOR3 ShotPosition;
	static const float MaxAngle;

private:
	MeshContainer * mesh;

	PlayerTurretRoot *turretRoot;
	std::vector<PlayerTurretActor*> turretContainer;

	std::shared_ptr<BoxCollider3D> collider;

	PlayerColliderViewer *colliderViewer;

	BaseEmitter *trailEmitter;

	float cntShotFrame;

	bool enableShot;
	bool enableMove;

	int currentLevel;

	void _Move(const D3DXVECTOR3& dir);
	void _Rotate(float dir);
	void _Shot();
	void _SlowDownEnemyBullet();

	virtual void OnColliderHit(ColliderObserver * other) override;
	virtual void OnFinishInitMove();
};

#endif