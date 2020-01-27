//=====================================
//
//PowerupItemActor.h
//�@�\:�p���[�A�b�v�A�C�e���A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _POWEUPITEMACTOR_H_
#define _POWEUPITEMACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
�O���錾
***************************************/
class BoxCollider3D;
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class PowerupItemActor : public BillboardObject, public ColliderObserver
{
public:
	PowerupItemActor();
	~PowerupItemActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static const D3DXVECTOR3 MoveBorder;

private:
	BoardPolygon * polygon;

	D3DXVECTOR3 moveDir;
	float cntFrame;

	std::shared_ptr<BoxCollider3D> collider;

	virtual void OnColliderHit(ColliderObserver * other) override;
};

#endif