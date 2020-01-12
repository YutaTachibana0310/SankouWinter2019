//=====================================
//
//PlayerActor.h
//機能:プレイヤーアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "../../../main.h"
#include <vector>
#include <functional>

/**************************************
前方宣言
***************************************/
class MeshContainer;
class PlayerTurretActor;
class PlayerTurretRoot;

/**************************************
クラス定義
***************************************/
class PlayerActor : public GameObject
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	std::function<void(const D3DXVECTOR3)> onFireBullet;

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;
	static const float MaxAngle;

private:
	MeshContainer * mesh;

	PlayerTurretRoot *turretRoot;
	std::vector<PlayerTurretActor*> turretContainer;

	float cntShotFrame;

	void _Move(const D3DXVECTOR3& dir);
	void _Rotate(float dir);
	void _Shot();
};

#endif