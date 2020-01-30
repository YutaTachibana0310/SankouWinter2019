//=====================================
//
//PlayerBomber.h
//機能:プレイヤーボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "../../../main.h"
#include "../../../Framework/Collider/BaseCollider.h"

/**************************************
前方宣言
***************************************/
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class PlayerBomberActor : public GameObject, public ColliderObserver
{
public:
	PlayerBomberActor();
	~PlayerBomberActor();

	void Init();
	void Uninit();
	void Update();

	virtual void OnColliderHit(ColliderObserver * other) override;

private:
	std::shared_ptr<BoxCollider3D> collider;
	float cntFrame;

};
#endif