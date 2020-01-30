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
#include "../System/ScoreRanking.h"
#include "../Viewer/Result/RankingViewer.h"

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
	ranking = new ScoreRanking();
	rankViewer = new RankingViewer();

	ranking->CheckUpdate();

	auto rankingContainer = ranking->GetRanking();
	rankViewer->SetRanking(rankingContainer);
}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(ranking);
	SAFE_DELETE(rankViewer);
}

/**************************************
更新処理
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
	rankViewer->Update();
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();
	viewer->Draw();
	rankViewer->Draw();
}
