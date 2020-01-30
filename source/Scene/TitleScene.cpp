//=====================================
//
//TitleScene.cpp
//機能:タイトルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/SkyBox.h"

#include "../Viewer/Title/TitleViewer.h"
#include "../BackGround/GameSkybox.h"
#include "../Actor/Title/TitlePlayerActor.h"
#include "../Effect/TitleParticleManager.h"
/**************************************

***************************************/

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");

	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	particleManager = TitleParticleManager::Instance();
	particleManager->Init();

	viewer = new TitleViewer();
	actor = new TitlePlayerActor();
	skybox = new SkyBox({ 30000.0f, 30000.0f, 30000.0f });

	const char* SkyboxTexture = "data/TEXTURE/Skybox/TitleSkybox.jpg";
	for (int i = 0; i < 6; i++)
	{
		skybox->LoadTexture(SkyboxTexture, SkyBox::Surface(i));
	}
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(actor);
	SAFE_DELETE(skybox);
	particleManager->Uninit();
}

/**************************************
更新処理
***************************************/
void TitleScene::Update()
{
	sceneCamera->Update();

	auto rotation = skybox->GetRotation();
	rotation.y += 0.01f;
	skybox->SetRotatition(rotation);

	actor->Update();
	viewer->Update();

	particleManager->Update();
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	sceneCamera->Set();
	skybox->Draw();
	actor->Draw();
	particleManager->Draw();
	viewer->Draw();
}
