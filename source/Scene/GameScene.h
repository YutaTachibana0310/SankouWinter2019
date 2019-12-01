//=====================================
//
//GameScene.h
//�@�\:�Q�[���V�[������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
�O���錾
***************************************/
class GameSkybox;
class PlayerActor;
class PlayerBulletController;
class BloomController;
class RenderingTarget;
class DemoEnemyActor;
class GameCamera;
class GameParticleManager;

/**************************************
�N���X��`
***************************************/
class GameScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static const float BloomPower[];
	static const float BloomThrethold[];

private:
	RenderingTarget * bloomTarget;
	GameSkybox * skybox;
	GameCamera *gameCamera;

	GameParticleManager *particleManager;

	PlayerActor *player;
	PlayerBulletController *bulletController;
	DemoEnemyActor *enemy;

	BloomController *bloom;

	void _DrawDebug();

};

#endif