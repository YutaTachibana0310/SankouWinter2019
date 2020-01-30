//=====================================
//
//ResultScene.cpp
//機能:リザルトシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../Viewer/Result/ResultViewer.h"
#include "../System/ScoreRanking.h"
#include "../Viewer/Result/RankingViewer.h"

/**************************************
グローバル変数
***************************************/
const float BloomPower[] = { 0.9f, 0.9f, 0.2f };		//ブルームの強さ
const float BloomThrethold[] = { 0.95f, 0.95f, 0.95f };		//ブルームをかける輝度の閾値

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
	bloom = new BloomController();

	bloom->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	bloom->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);

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
	SAFE_DELETE(bloom);
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

	bloom->Draw(renderTexture);
}
