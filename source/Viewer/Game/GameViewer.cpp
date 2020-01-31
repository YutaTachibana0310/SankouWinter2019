//=====================================
//
// GameViewer.cpp
// 機能:ゲームビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

#include "ScoreViewer.h"
#include "EnergyViewer.h"
#include "BomberViewer.h"
#include "LifeViewer.h"
#include "GameTelop.h"
#include "../../Sound/SoundPlayer.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
GameViewer::GameViewer()
{
	bg = new Polygon2D();
	bg->SetSize({ (float)SCREEN_WIDTH / 2.0f, (float)55.0f});
	bg->SetPosition({ SCREEN_CENTER_X, 55.0f, 0.0f });
	bg->LoadTexture("data/TEXTURE/Viewer/ViewerBelt.png");
	bg->SetUV(0.0f, 0.0f, 1.0f, 1.0f);

	scoreViewer = new ScoreViewer();
	energyViewer = new EnergyViewer();
	bomberViewer = new BomberViewer();
	lifeViewer = new LifeViewer();
	telop = new GameTelop();
}

/**************************************
デストラクタ
***************************************/
GameViewer::~GameViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(scoreViewer);
	SAFE_DELETE(energyViewer);
	SAFE_DELETE(bomberViewer);
	SAFE_DELETE(lifeViewer);
	SAFE_DELETE(telop);
}

/**************************************
更新処理
***************************************/
void GameViewer::Update()
{
	scoreViewer->Update();
	energyViewer->Update();
	bomberViewer->Update();
	lifeViewer->Update();
}

/**************************************
描画処理
***************************************/
void GameViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	bg->Draw();

	scoreViewer->Draw();

	energyViewer->Draw();

	bomberViewer->Draw();

	lifeViewer->Draw();

	telop->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

/**************************************
描画パラメータ設定処理
***************************************/
void GameViewer::SetParameter(const GameViewerParameter & param)
{
	energyViewer->SetPercent(param.percentEnergy);
	bomberViewer->SetCount(param.cntBomb);
	lifeViewer->SetCount(param.cntLife);
}

/**************************************
ゲームスタートテロップ再生
***************************************/
void GameViewer::PlayGameStart(const std::function<void()>& callback)
{
	telop->Play(GameTelop::GameStart, callback);
	SoundPlayer::Instance()->Play("GameStart");
}

/**************************************
ステージクリアテロップ再生
***************************************/
void GameViewer::PlayStageClear(const std::function<void()>& callback)
{
	telop->Play(GameTelop::StageClear, callback);
	SoundPlayer::Instance()->Play("StageClear");
}

/**************************************
ゲームオーバーテロップ再生
***************************************/
void GameViewer::PlayGameOvert(const std::function<void()>& callback)
{
	telop->Play(GameTelop::GameOver, callback);
	SoundPlayer::Instance()->Play("GameOver");
}
