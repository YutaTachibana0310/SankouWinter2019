//=====================================
//
//SceneTutorial.h
//機能:チュートリアルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCENETUTORIAL_H_
#define _SCENETUTORIAL_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/
class GameSkybox;
class BloomController;
class RenderingTarget;
class EnemyController;
class GameCamera;
class GameParticleManager;
class PlanetActor;
class GameViewer;
class PlayerController;
class BackViewer;
class EnemyEventHandler;

/**************************************
クラス定義
***************************************/
class TutorialScene : public BaseScene
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
	GameCamera *gameCamera;

	GameParticleManager *particleManager;

	PlayerController *playerController;

	EnemyController *enemyController;

	BloomController *bloom;

	GameViewer *viewer;
	BackViewer *backViewer;

	EnemyEventHandler *handler;
};
#endif