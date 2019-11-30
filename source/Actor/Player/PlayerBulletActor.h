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

/**************************************
前方宣言
***************************************/
class BoardPolygon;

/**************************************
クラス定義
***************************************/
class PlayerBulletActor : public GameObject
{
public:
	PlayerBulletActor();
	~PlayerBulletActor();

	void Init(const D3DXVECTOR3& position);
	void Uninit();
	void Update();
	void Draw();

	static const float SpeedMove;
	static const D3DXVECTOR3 MoveBorder;

	bool operator<(const PlayerBulletActor& rhs) const;
	bool operator>(const PlayerBulletActor& rhs) const;

	static const D3DXVECTOR2 Size;

private:
	BoardPolygon * polygon;

	bool _IsOutBorder();
};
#endif