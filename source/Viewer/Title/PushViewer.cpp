//=====================================
//
//PushViewer.cpp
//機能:プッシュビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PushViewer.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/
static const float DurationFade = 90.0f;

/**************************************
コンストラクタ
***************************************/
PushViewer::PushViewer()
{
	polygon = std::make_shared<Polygon2D>();
	polygon->LoadTexture("data/TEXTURE/Viewer/PushButton.png");
	polygon->SetSize({ 256.0f, 45.0f });
	polygon->SetPosition({ SCREEN_CENTER_X, 600.0f, 0.0f });

	onFinishFadeIn = std::bind(&PushViewer::OnFinishFadeIn, this);
	onFinishFadeOut = std::bind(&PushViewer::OnFinishFadeOut, this);

	Tween::Fade(polygon, 1.0f, 0.0f, DurationFade, EaseType::Linear, true, onFinishFadeOut);
}

/**************************************
デストラクタ
***************************************/
PushViewer::~PushViewer()
{
	polygon.reset();
}

/**************************************
描画処理
***************************************/
void PushViewer::Draw()
{
	polygon->Draw();
}

/**************************************
フェードインコールバック
***************************************/
void PushViewer::OnFinishFadeIn()
{
	Tween::Fade(polygon, 1.0f, 0.0f, DurationFade, EaseType::Linear, true, onFinishFadeOut);
}

/**************************************
フェードアウトコールバック
***************************************/
void PushViewer::OnFinishFadeOut()
{
	Tween::Fade(polygon, 0.0f, 1.0f, DurationFade, EaseType::Linear, true, onFinishFadeIn);
}
