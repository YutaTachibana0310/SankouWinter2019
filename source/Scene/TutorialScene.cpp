//=====================================
//
//SceneTutorial.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Collider/ColliderManager.h"
#include "../../Framework/Input/input.h"
#include "../../Framework/Transition/TransitionController.h"
#include "../../Framework/Core/SceneManager.h"

#include "../GameConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Camera/GameCamera.h"
#include "../Controller/PlayerBulletController.h"
#include "../Controller/EnemyController.h"
#include "../Controller/EnemyTimeController.h"
#include "../Viewer/Game/GameViewer.h"
#include "../Controller/TutorialPlayerController.h"
#include "../Sound/MusicPlayer.h"
#include "../Viewer/Back/BackViewer.h"
#include "../Handler/EnemyEventHandler.h"
#include "../Handler/EnergyHandler.h"

#include "../System/GameScore.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const float TutorialScene::BloomPower[] = { 0.9f, 0.85f, 0.76f };		//�u���[���̋���
const float TutorialScene::BloomThrethold[] = { 0.4f, 0.3f, 0.24f };		//�u���[����������P�x��臒l

/**************************************
����������
***************************************/
void TutorialScene::Init()
{
	GameScore::Instance()->Init();

	particleManager = GameParticleManager::Instance();
	particleManager->Init();

	MusicPlayer::PlayBGM(GameBGM);

	sceneCamera = gameCamera = new GameCamera();
	backViewer = new BackViewer();

	playerController = new TutorialPlayerController(gameCamera, backViewer);
	bloom = new BloomController();
	enemyController = new EnemyController(gameCamera);
	viewer = new GameViewer();
	handler = new EnemyEventHandler();

	auto energyHandler = std::make_shared<EnergyHandler>(playerController);
	particleManager->CreateEnergyEffectController(energyHandler);

	Camera::SetMainCamera(gameCamera);

	handler->GivePlayerController(playerController);
	handler->GiveBackViewer(backViewer);
	enemyController->SetEnemyEventHandler(handler);

	bloom->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	bloom->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);

	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [this]()
	{
		playerController->Init();
	});

	particleManager->RunUpdate();
}

/**************************************
�I������
***************************************/
void TutorialScene::Uninit()
{
	particleManager->StopUpdate([this]()
	{
		SAFE_DELETE(gameCamera);
		SAFE_DELETE(playerController);
		SAFE_DELETE(bloom);
		SAFE_DELETE(enemyController);
		SAFE_DELETE(viewer);
		SAFE_DELETE(backViewer);
		SAFE_DELETE(handler);

		particleManager->Uninit();

		sceneCamera = nullptr;
	});
}

/**************************************
�X�V����
***************************************/
void TutorialScene::Update()
{
	gameCamera->Update();
	playerController->Update();
	enemyController->Update();

	ColliderManager::Instance()->Update();
	ColliderManager::Instance()->CheckRoundRobin("PlayerShield", "EnemyBullet");
	ColliderManager::Instance()->CheckRoundRobin("PlayerBullet", "Enemy");
	ColliderManager::Instance()->CheckRoundRobin("PlayerBomber", "EnemyBullet");
	ColliderManager::Instance()->CheckRoundRobin("PlayerBomber", "Enemy");
	ColliderManager::Instance()->CheckRoundRobin("Player", "Enemy");
	ColliderManager::Instance()->CheckRoundRobin("Player", "EnemyBullet");
	ColliderManager::Instance()->CheckRoundRobin("Player", "Item");

	enemyController->CheckEnemyDestroy();

	viewer->Update();

	if (Keyboard::GetTrigger(DIK_F5))
		SceneManager::ChangeScene(GameConfig::Result);
}

/**************************************
�`�揈��
***************************************/
void TutorialScene::Draw()
{
	Camera::MainCamera()->Set();

	backViewer->Draw();

	playerController->Draw();

	enemyController->Draw();

	playerController->DrawBullet();

	//�u���[����������
	bloom->Draw(renderTexture);

	particleManager->Draw();

	enemyController->DrawBullet();

	playerController->DrawCollider();

	GameViewerParameter param(
		playerController->GetPercentEnergy(),
		playerController->GetCntLife(),
		playerController->GetCntBomb()
	);
	viewer->SetParameter(param);
	viewer->Draw();

	particleManager->DrawEnergyEffect();
}
