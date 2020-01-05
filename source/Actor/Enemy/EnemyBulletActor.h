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
#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../Controller/EnemyBulletConfig.h"

/**************************************
�O���錾
***************************************/
class BoxCollider3D;
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class EnemyBulletActor : public BillboardObject, public ColliderObserver
{
public:
	EnemyBulletActor();
	~EnemyBulletActor();

	void Init(const Transform& shotTransform);
	void Uninit();
	void Update();
	void Draw();
	void DrawBloom();

	void SetType(EnemyBulletConfig::Type type);
	void SetSpeed(float speed);

	static const D3DXVECTOR3 SizeCollider;
	static const int IntervalAnimation;
	static const D3DXVECTOR3 BorderLeftTop;
	static const D3DXVECTOR3 BorderRightBottom;

	void OnColliderHit(ColliderObserver * other) override;

private:
	std::shared_ptr<BoxCollider3D> collider;
	BoardPolygon *polygon;

	BillboardTransform *renderTransform;

	EnemyBulletConfig::Type type;

	int cntFrame;
	int indexAnim;

	float speed;

	bool CheckMoveBorder() const;
};

#endif