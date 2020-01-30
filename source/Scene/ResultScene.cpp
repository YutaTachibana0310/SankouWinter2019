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
#include "../../Framework/Tween/Tween.h"
#include "../../Framework/Input/input.h"
#include "../../Framework/Transition/TransitionController.h"
#include "../../Framework/Core/SceneManager.h"

#include "../GameConfig.h"
#include "../Viewer/Result/ResultViewer.h"
#include "../System/ScoreRanking.h"
#include "../Viewer/Result/RankingViewer.h"

/**************************************
グローバル変数
***************************************/
static const float BloomPower[] = { 0.9f, 0.9f, 0.3f };		//ブルームの強さ
static const float BloomThrethold[] = { 0.95f, 0.95f, 0.95f };		//ブルームをかける輝度の閾値
static const float BlinkDuraiton = 120.0f;

/**************************************
初期化処理
***************************************/
void ResultScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	onFinishBlinkIn = std::bind(&ResultScene::OnFinishBlinkIn, this);
	onFinishBlinkOut = std::bind(&ResultScene::OnFinishBlinkOut, this);

	bloomPower = std::make_shared<float>();
	*bloomPower = 1.0f;

	viewer = new ResultViewer();
	ranking = new ScoreRanking();
	rankViewer = new RankingViewer();
	bloom = new BloomController();

	bloom->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	bloom->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);

	ranking->CheckUpdate();

	OnFinishBlinkIn();

	inTransition = true;
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [this]()
	{
		inTransition = false;
		auto rankingContainer = ranking->GetRanking();
		rankViewer->SetRanking(rankingContainer);
		rankViewer->MoveIn();
	});
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
	bloomPower.reset();
}

/**************************************
更新処理
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
	rankViewer->Update();

	bloom->SetPower(BloomPower[0] * *bloomPower, BloomPower[1] * *bloomPower, BloomPower[2] * *bloomPower);

	if (!inTransition && Keyboard::GetTrigger(DIK_Z))
	{
		inTransition = true;
		TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, []()
		{
			SceneManager::ChangeScene(GameConfig::Title);
		});
	}
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	viewer->Draw();
	rankViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	bloom->Draw(renderTexture);
}

/**************************************
ブルーム点滅コールバック
***************************************/
void ResultScene::OnFinishBlinkIn()
{
	Tween::To(bloomPower, 0.5f, BlinkDuraiton, EaseType::Linear, true, onFinishBlinkOut);
}

/**************************************
ブルーム点滅コールバック
***************************************/
void ResultScene::OnFinishBlinkOut()
{
	Tween::To(bloomPower, 1.0f, BlinkDuraiton, EaseType::Linear, true, onFinishBlinkIn);
}
