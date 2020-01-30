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
#include "../../Framework/Pattern/BaseState.h"

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
class TutorialPlayerController;
class BackViewer;
class EnemyEventHandler;
class TutorialViewer;

/**************************************
クラス定義
***************************************/
class TutorialScene : public BaseScene
{
	using BaseScene::BaseScene;

public:
	enum State
	{
		Move,
		Attack,
		Slowdown,
		Bomber,
		Wait,
		Max
	};

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static const float BloomPower[];
	static const float BloomThrethold[];

	using TutorialState = BaseState<TutorialScene, State>;

private:
	GameCamera *gameCamera;

	GameParticleManager *particleManager;

	TutorialPlayerController *playerController;

	EnemyController *enemyController;

	BloomController *bloom;

	GameViewer *viewer;
	BackViewer *backViewer;

	EnemyEventHandler *handler;

	TutorialViewer *tutorialViewer;

	State state;
	State prevState;
};
#endif