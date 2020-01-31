//=====================================
//
//SceneTutorial.cpp
//機能:
//Author:GP12B332 21 立花雄太
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
#include "../../Framework/Renderer3D/SkyBox.h"

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
#include "../Viewer/Tutorial/TutorialViewer.h"
#include "../System/GameInput.h"
#include "../System/GameScore.h"
#include "../Sound/MusicPlayer.h"

/**************************************
グローバル変数
***************************************/
const float TutorialScene::BloomPower[] = { 0.9f, 0.85f, 0.76f };		//ブルームの強さ
const float TutorialScene::BloomThrethold[] = { 0.4f, 0.3f, 0.24f };		//ブルームをかける輝度の閾値

/**************************************
初期化処理
***************************************/
void TutorialScene::Init()
{
	GameScore::Instance()->Init();

	particleManager = GameParticleManager::Instance();
	particleManager->Init();

	sceneCamera = gameCamera = new GameCamera();
	backViewer = new BackViewer();

	playerController = new TutorialPlayerController(gameCamera, backViewer);
	bloom = new BloomController();
	enemyController = new EnemyController(gameCamera);
	viewer = new GameViewer();
	handler = new EnemyEventHandler();
	tutorialViewer = new TutorialViewer();
	skybox = new SkyBox({ 5000.0f, 2000.0f, 2000.0f });

	for (int i = 0; i < SkyBox::Surface::Max; i++)
	{
		skybox->LoadTexture("data/TEXTURE/Skybox/TutorialGrid.jpg", SkyBox::Surface(i));
	}

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
		state = State::Move;
	});

	particleManager->RunUpdate();

	state = State::Wait;
	cntFrame = 0;

	MusicPlayer::FadeIn(TutorialBGM, 60);
}

/**************************************
終了処理
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
		SAFE_DELETE(tutorialViewer);
		SAFE_DELETE(skybox);

		particleManager->Uninit();

		sceneCamera = nullptr;
	});
}

/**************************************
更新処理
***************************************/
void TutorialScene::Update()
{
	switch (state)
	{
	case Move:
		tutorialViewer->Set(TutorialViewer::Move, nullptr);
		state = MoveWait;
		break;

	case MoveWait:
		++cntFrame;
		if (cntFrame == 270)
		{
			cntFrame = 0;
			state = Attack;
		}
		break;

	case Attack:
		playerController->EnableShot(true);
		enemyController->CreateTutorialEnemy();
		tutorialViewer->Set(TutorialViewer::Attack, nullptr);
		state = AttackWait;
		break;

	case AttackWait:
		if (GameInput::GetShotButtonPress())
			++cntFrame;

		if (cntFrame == 240)
		{
			cntFrame = 0;
			state = Slowdown;
		}
		break;

	case Slowdown:
		playerController->EnableSlowdown(true);
		tutorialViewer->Set(TutorialViewer::SlowDown, nullptr);
		state = SlowdownWait;
		break;

	case SlowdownWait:
		if (GameInput::GetSlowdownButtonPress())
			++cntFrame;

		if (cntFrame == 120)
		{
			cntFrame = 0;
			state = Bomber;
		}
		break;

	case Bomber:
		tutorialViewer->Set(TutorialViewer::Bomber, nullptr);
		playerController->EnableBomber(true);
		state = BomberWait;
		break;

	case BomberWait:
		if (GameInput::GetBomberButtonTrigger())
		{
			state = Finish;
		}
		break;

	case Finish:
		cntFrame++;
		if (cntFrame == 300)
		{
			MusicPlayer::FadeOut(60);
			TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, []()
			{
				SceneManager::ChangeScene(GameConfig::Game);
			});
		}
		break;
	}

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
}

/**************************************
描画処理
***************************************/
void TutorialScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();

	backViewer->Draw();

	playerController->Draw();

	enemyController->Draw();

	playerController->DrawBullet();

	//ブルームをかける
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

	tutorialViewer->Draw();
}
