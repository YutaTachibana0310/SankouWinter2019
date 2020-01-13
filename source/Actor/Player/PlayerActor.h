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