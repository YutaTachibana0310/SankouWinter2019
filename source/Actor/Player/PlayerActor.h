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

/**************************************
前方宣言
***************************************/
class MeshContainer;
class PlayerTurretActor;

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

	static const float SpeedMove;
	static const D3DXVECTOR3 BorderMove;
	static const float MaxAngle;
private:
	MeshContainer * mesh;

	Transform *turretTransform;
	std::vector<PlayerTurretActor*> turretContainer;

	void _Move(const D3DXVECTOR3& dir);
	void _Rotate(float dir);
};

#endif