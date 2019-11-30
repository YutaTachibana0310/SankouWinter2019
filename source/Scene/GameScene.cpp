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

#include "../BackGround/GameSkybox.h"
#include "../Actor/Player/PlayerActor.h"
#include "../Controller/PlayerBulletController.h"

/**************************************
staticメンバ
***************************************/
const float GameScene::BloomPower[] = { 0.9f, 0.75f, 0.6f };		//ブルームの強さ
const float GameScene::BloomThrethold[] = { 0.6f, 0.5f, 0.24f };		//ブルームをかける輝度の閾値

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	ResourceManager::Instance()->MakePolygon("BlazeBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });

	sceneCamera = new Camera();
	bloomTarget = new RenderingTarget(SCREEN_WIDTH, SCREEN_HEIGHT);
	skybox = new GameSkybox();
	player = new PlayerActor();
	bulletController = new PlayerBulletController();
	bloom = new BloomController();

	Camera::SetMainCamera(sceneCamera);

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1);
	player->onFireBullet = onFireBullet;

	player->Init();

	bloom->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	bloom->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(bloomTarget);
	SAFE_DELETE(skybox);
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);
	SAFE_DELETE(bloom);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
	player->Update();
	bulletController->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	Camera::MainCamera()->Set();

	skybox->Draw();

	bloomTarget->Set();

	player->Draw();

	bulletController->Draw();

	bloomTarget->Restore();

	bloomTarget->Draw();

	//ブルームをかける
	bloom->Draw(bloomTarget->GetTexture());

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

	Debug::End();
}
