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

	PlayerController *playerController;

	EnemyController *enemyController;
	PlanetActor *planet;

	BloomController *bloom;

	GameViewer *viewer;
	BackViewer *backViewer;

	EnemyEventHandler *handler;

	void _DrawDebug();

	void _OnGameOver();
};

#endif