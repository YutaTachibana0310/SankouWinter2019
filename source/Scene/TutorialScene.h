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
class SkyBox;
class RenderingTarget;

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
		MoveWait,
		Attack,
		AttackWait,
		Slowdown,
		SlowdownWait,
		Bomber,
		BomberWait,
		Wait,
		Finish,
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
	RenderingTarget * bloomTarget;
	GameParticleManager *particleManager;

	TutorialPlayerController *playerController;

	EnemyController *enemyController;

	BloomController *bloom;

	GameViewer *viewer;
	BackViewer *backViewer;

	EnemyEventHandler *handler;

	TutorialViewer *tutorialViewer;

	SkyBox *skybox;

	State state;
	State prevState;

	int cntFrame;
};
#endif