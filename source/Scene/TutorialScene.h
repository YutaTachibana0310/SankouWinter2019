//=====================================
//
//SceneTutorial.h
//�@�\:�`���[�g���A���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCENETUTORIAL_H_
#define _SCENETUTORIAL_H_

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