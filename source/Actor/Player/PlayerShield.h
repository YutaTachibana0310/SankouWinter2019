//=====================================
//
//PlayerShield.h
//機能:プレイヤーシールド
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERSHIELD_H_
#define _PLAYERSHIELD_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class PlayerShield : public BillboardObject, public ColliderObserver
{
public:
	PlayerShield();
	~PlayerShield();

	void Update();
	void Draw();

	void SetActive(bool state) override;

	virtual void OnColliderHit(ColliderObserver * other) override;

private:
	std::shared_ptr<BoxCollider3D> collider;
	BoardPolygon *polygon;
};
#endif