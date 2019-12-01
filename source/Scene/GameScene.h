//=====================================
//
//GameScene.h
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
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
クラス定義
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