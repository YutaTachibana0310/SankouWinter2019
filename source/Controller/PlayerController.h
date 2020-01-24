//=====================================
//
//PlayerController.h
//�@�\:�v���C���[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class PlayerActor;
class PlayerBulletController;
class ColliderObserver;
class GameCamera;

/**************************************
�N���X��`
***************************************/
class PlayerController
{
public:
	PlayerController(GameCamera *camera);
	~PlayerController();

	void Update();
	void Draw();
	void DrawBullet();
	void DrawCollider();

	float GetPercentEnergy() const;
	int GetCntLife() const;
	int GetCntBomb() const;

	bool InSlowdown() const;

	D3DXVECTOR3 GetPlayerPosition() const;

private:
	PlayerActor * player;
	PlayerBulletController *bulletController;

	GameCamera *camera;

	float cntEnergy;
	bool inSlow;

	int cntBomb;
	int cntLife;

	static const float MaxEnergy;
	static const int MaxLife;
	static const int MaxBomb;

	void SlowDownEnemyBullet(bool isSlow);
	void CollisionPlayer(ColliderObserver* other);
	void OnFinishCameraFocus();
};
#endif