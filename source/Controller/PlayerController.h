//=====================================
//
//PlayerController.h
//機能:プレイヤーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include "../../main.h"
#include <vector>
#include <functional>

/**************************************
前方宣言
***************************************/
class PlayerActor;
class PlayerBulletController;
class ColliderObserver;
class GameCamera;
class PowerupItemActor;
class BackViewer;
class PlayerBomberActor;

/**************************************
クラス定義
***************************************/
class PlayerController
{
public:
	PlayerController(GameCamera *camera, BackViewer *backViewer);
	virtual ~PlayerController();

	void Init();
	void Update();
	void Draw();
	void DrawBullet();
	void DrawCollider();

	float GetPercentEnergy() const;
	int GetCntLife() const;
	int GetCntBomb() const;

	bool InSlowdown() const;

	D3DXVECTOR3 GetPlayerPosition() const;

	void SetPowerupItem(const D3DXVECTOR3& position);

	void AddEnergy(float energy);

	std::function<void()> onGameOver;

protected:
	PlayerActor * player;
	PlayerBulletController *bulletController;
	PlayerBomberActor *bomber;

	std::vector<PowerupItemActor*> itemContainer;

	GameCamera *camera;
	BackViewer *backViewer;

	float cntEnergy;
	bool inSlow;

	int cntBomb;
	int cntLife;

	static const float MaxEnergy;
	static const int MaxLife;
	static const int MaxBomb;

	virtual void SlowDownEnemyBullet(bool isSlow);
	void CollisionPlayer(ColliderObserver* other);
	void OnFinishCameraFocus();
	virtual void FireBomber();
};
#endif