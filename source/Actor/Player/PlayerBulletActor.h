//=====================================
//
//PlayerBulletActor.h
//機能:プレイヤーバレットアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERULLETACTOR_H_
#define _PLAYERULLETACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Collider/ColliderObserver.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;
class BoxCollider3D;

/**************************************
クラス定義
***************************************/
class PlayerBulletActor : public GameObject, public ColliderObserver
{
public:
	PlayerBulletActor();
	~PlayerBulletActor();

	void Init(const D3DXVECTOR3& position, bool isMain, int level);
	void Uninit();
	void Update();
	void Draw();

	virtual void OnColliderHit(ColliderObserver * other) override;

	inline float Power()
	{
		return power;
	}

	static const float SpeedMove;
	static const D3DXVECTOR3 MoveBorder;

	bool operator<(const PlayerBulletActor& rhs) const;
	bool operator>(const PlayerBulletActor& rhs) const;

	static const D3DXVECTOR2 Size;

private:
	BoardPolygon * polygon;
	std::shared_ptr<BoxCollider3D> collider;

	bool _IsOutBorder();

	float power;

	static const float PowerTable[];
};
#endif