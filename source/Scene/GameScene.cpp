//=====================================
//
//GameScene.cpp
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Renderer2D/RenderingTarget.h"

#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Collider/ColliderManager.h"
#include "../../Framework/Input/input.h"
#include "../../Framework/Transition/TransitionController.h"

#include "../Effect/GameParticleManager.h"
#include "../Camera/GameCamera.h"
#include "../BackGround/GameSkybox.h"
#include "../BackGround/PlanetActor.h"
#include "../Actor/Player/PlayerActor.h"
#include "../Controller/PlayerBulletController.h"
#include "../Controller/EnemyController.h"
#include "../Controller/EnemyTimeController.h"
#include "../Viewer/Game/GameViewer.h"
#include "../Controller/PlayerController.h"
#include "../Sound/MusicPlayer.h"
#include "../Viewer/Back/BackViewer.h"
#include "../Handler/EnemyEventHandler.h"
#include "../Handler/EnergyHandler.h"

/**************************************
staticメンバ
***************************************/
const float GameScene::BloomPower[] = { 0.9f, 0.85f, 0.76f };		//ブルームの強さ
const float GameScene::BloomThrethold[] = { 0.4f, 0.3f, 0.24f };		//ブルームをかける輝度の閾値

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop);

	ResourceManager::Instance()->LoadMesh("Planet", "data/MODEL/Planet/GreyMoon.x");

	particleManager = GameParticleManager::Instance();
	particleManager->Init();

	MusicPlayer::PlayBGM(GameBGM);

	sceneCamera = gameCamera = new GameCamera();
	backViewer = new BackViewer();

	bloomTarget = new RenderingTarget(SCREEN_WIDTH, SCREEN_HEIGHT);
	skybox = new GameSkybox();
	playerController = new PlayerController(gameCamera, backViewer);
	bloom = new BloomController();
	enemyController = new EnemyController(gameCamera);
	planet = new PlanetActor();
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
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(gameCamera);
	SAFE_DELETE(bloomTarget);
	SAFE_DELETE(skybox);
	SAFE_DELETE(playerController);
	SAFE_DELETE(bloom);
	SAFE_DELETE(enemyController);
	SAFE_DELETE(planet);
	SAFE_DELETE(viewer);
	SAFE_DELETE(backViewer);
	SAFE_DELETE(handler);

	particleManager->Uninit();

	sceneCamera = nullptr;
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	gameCamera->Update();
	skybox->Update();
	playerController->Update();
	enemyController->Update();
	planet->Update();

	ColliderManager::Instance()->CheckRoundRobin("PlayerBullet", "Enemy");
	ColliderManager::Instance()->CheckRoundRobin("Player", "EnemyBullet");
	ColliderManager::Instance()->CheckRoundRobin("Player", "Item");

	enemyController->CheckEnemyDestroy();

	particleManager->Update();

	viewer->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();

	backViewer->Draw();

	bloomTarget->Set();

	planet->Draw();
	
	playerController->Draw();

	enemyController->Draw();

	playerController->DrawBullet();

	bloomTarget->Restore();

	bloomTarget->Draw();

	//ブルームをかける
	bloom->Draw(bloomTarget->GetTexture());

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

	_DrawDebug();
}

/**************************************
デバッグ表示
***************************************/
void GameScene::_DrawDebug()
{
	Debug::Begin("GameDebug");

	static float bloomPower[]{ BloomPower[0], BloomPower[1], BloomPower[2] };
	static float bloomThrethold[]{ BloomThrethold[0], BloomThrethold[1], BloomThrethold[2] };

	Debug::Slider("power0", bloomPower[0], 0.0f, 1.0f);
	Debug::Slider("power1", bloomPower[1], 0.0f, 1.0f);
	Debug::Slider("power2", bloomPower[2], 0.0f, 1.0f);

	Debug::Slider("threth0", bloomThrethold[0], 0.0f, 1.0f);
	Debug::Slider("threth1", bloomThrethold[1], 0.0f, 1.0f);
	Debug::Slider("threth2", bloomThrethold[2], 0.0f, 1.0f);

	bloom->SetPower(bloomPower[0], bloomPower[1], bloomPower[2]);
	bloom->SetThrethold(bloomThrethold[0], bloomThrethold[1], bloomThrethold[2]);

	if (Debug::Button("TimeBreak"))
	{
		backViewer->PlayTimeBreak();
	}

	Debug::End();
}
