//=====================================
//
// EnemyBulletActor.h
// �@�\:�G�l�~�[�o���b�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETACTOR_H_
#define _ENEMYBULLETACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
�O���錾
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
�N���X��`
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