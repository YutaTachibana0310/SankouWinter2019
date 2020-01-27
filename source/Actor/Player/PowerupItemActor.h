//=====================================
//
//PowerupItemActor.h
//機能:パワーアップアイテムアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POWEUPITEMACTOR_H_
#define _POWEUPITEMACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
前方宣言
***************************************/
class BoxCollider3D;
class BoardPolygon;

/**************************************
クラス定義
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