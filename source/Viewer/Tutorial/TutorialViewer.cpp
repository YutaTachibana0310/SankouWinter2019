//=====================================
//
//TutorialViewer.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Task/TaskManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TutorialViewer::TutorialViewer() :
	callback(nullptr)
{
	textAlpha = std::make_shared<float>(0.0f);

	bg = std::make_shared<Polygon2D>();
	bg->LoadTexture("");
	bg->SetSize({ 500.0f, 130.0f });
	bg->SetColor(D3DXCOLOR(0.01f, 0.01f, 0.1f, 0.0f));

	text = new TextViewer("マキナス 4 Square", 60);
	
	const D3DXVECTOR3 Position = { SCREEN_CENTER_X, 300.0f, 0.0f };
	text->SetPosition(Position);
	bg->SetPosition(Position);

	onFinisheFadeIn = std::bind(&TutorialViewer::_OnFinishFadeIn, this);
}

/**************************************
デストラクタ
***************************************/
TutorialViewer::~TutorialViewer()
{
	textAlpha.reset();
	bg.reset();

	SAFE_DELETE(text);
}

/**************************************
更新処理
***************************************/
void TutorialViewer::Update()
{
}

/**************************************
描画処理
***************************************/
void TutorialViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	bg->Draw();

	text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, *textAlpha));
	text->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

/**************************************
セット処理
***************************************/
void TutorialViewer::Set(State state, const std::function<void()>& callback)
{
	this->callback = callback;

	switch (state)
	{
	case State::Move:
		text->SetText("チュートリアル1\n左スティック、矢印キーで移動ができます");
		break;
	
	case State::Attack:
		text->SetText("チュートリアル2\nZキー、□ボタンで攻撃ができます");
		break;

	case State::SlowDown:
		text->SetText("チュートリアル3\nCキー,Rボタンで青い弾を止められます");
		break;

	case State::Bomber:
		text->SetText("チュートリアル4\nXキー、Xボタンでボンバーが撃てます");
		break;
	}

	Tween::To(textAlpha, 1.0f, 60.0f, EaseType::Linear, true);
	Tween::Fade(bg, 0.0f, 0.8f, 60.0f,  EaseType::Linear, true, onFinisheFadeIn);
}

/**************************************
フェードイン終了コールバック
***************************************/
void TutorialViewer::_OnFinishFadeIn()
{
	TaskManager::Instance()->CreateDelayedTask(150.0f, true, [this]()
	{
		Tween::To(textAlpha, 0.0f, 60.0f, EaseType::Linear, true);
		Tween::Fade(bg, 0.8f, 0.0f, 60.0f, EaseType::Linear, true, callback);
	});
}
