//=====================================
//
//TimeBreakText.cpp
//機能:TIME BREAKテキスト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TimeBreakText.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Task/TaskManager.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 TimeBreakText::InitPositionUpper = { SCREEN_WIDTH * 1.5f, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::InitPositionLower = { SCREEN_WIDTH * -0.5f, 830.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::PositionUpper = { SCREEN_CENTER_X, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::PositionLower = { SCREEN_CENTER_X, 830.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::LastPositionUpper = { SCREEN_WIDTH * -0.5f, 350.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::LastPositionLower = { SCREEN_WIDTH * 1.5f, 830.0f, 0.0f };

/**************************************
コンストラクタ
***************************************/
TimeBreakText::TimeBreakText()
{
	upper = new Polygon2D();
	lower = new Polygon2D();

	upper->LoadTexture("data/TEXTURE/Viewer/TimeBreak.png");
	lower->LoadTexture("data/TEXTURE/Viewer/TimeBreak.png");

	upper->SetPosition(InitPositionUpper);
	lower->SetPosition(InitPositionLower);

	upper->SetSize({ 960.0f, 270.0f });
	lower->SetSize({ 960.0f, 270.0f });

	upper->SetUV(0.0f, 0.0f, 1.0f, 0.5f);
	lower->SetUV(0.0f, 0.5f, 1.0f, 0.5f);
}

/**************************************
デストラクタ
***************************************/
TimeBreakText::~TimeBreakText()
{
	SAFE_DELETE(upper);
	SAFE_DELETE(lower);
}

/**************************************
描画処理
***************************************/
void TimeBreakText::Draw()
{
	upper->Draw();
	lower->Draw();
}

/**************************************
セット処理
***************************************/
void TimeBreakText::Set()
{
	upper->SetPosition(InitPositionUpper);
	lower->SetPosition(InitPositionLower);

	auto callback = std::bind(&TimeBreakText::OnFinishIn, this);
	Tween::Move(*upper, PositionUpper, 60.0f, EaseType::OutCubic, true);
	Tween::Move(*lower, PositionLower, 60.0f, EaseType::OutCubic, true, callback);
}

/**************************************
テキストイン終了コールバック
***************************************/
void TimeBreakText::OnFinishIn()
{
	TaskManager::Instance()->CreateDelayedTask(60.0f, true, [=]()
	{
		Tween::Move(*upper, LastPositionUpper, 60.0f, EaseType::InCubic, true);
		Tween::Move(*lower, LastPositionLower, 60.0f, EaseType::InCubic, true);
	});
}

/**************************************
テキストアウト終了コールバック
***************************************/
void TimeBreakText::OnFinishOut()
{
}
