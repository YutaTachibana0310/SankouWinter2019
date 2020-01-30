//=====================================
//
//TitleScene.cpp
//機能:タイトルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../Viewer/Title/TitleViewer.h"
#include "../BackGround/GameSkybox.h"

/**************************************

***************************************/

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	viewer = new TitleViewer();
	skybox = new GameSkybox();
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(skybox);
}

/**************************************
更新処理
***************************************/
void TitleScene::Update()
{
	sceneCamera->Update();
	skybox->Update();
	viewer->Update();
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	sceneCamera->Set();
	skybox->Draw();
	viewer->Draw();
}
