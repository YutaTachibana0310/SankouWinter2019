//=====================================
//
//ResultScene.cpp
//機能:リザルトシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Camera/Camera.h"

#include "../Viewer/Result/ResultViewer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void ResultScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	viewer = new ResultViewer();
}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
}

/**************************************
更新処理
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();
	viewer->Draw();
}
