//=====================================
//
//PlayerTurretActor.h
//機能:プレイヤー砲台アクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERTURRETACTOR_H_
#define _PLAYERTURRETACTOR_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class PlayerTurretActor : public GameObject
{
public:
	PlayerTurretActor();
	~PlayerTurretActor();

	void Update();
	void Draw();

	D3DXVECTOR3 GetShotPosition() const;

private:
	MeshContainer * mesh;

	static const D3DXVECTOR3 OffsetShot;
};

/**************************************
PlayerTurretRootクラス
***************************************/
class PlayerTurretRoot : public GameObject
{
	using GameObject::GameObject;

public:
	void Update();
};
#endif