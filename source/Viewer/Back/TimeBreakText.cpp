//=====================================
//
//TimeBreakText.cpp
//機能:TIME BREAKテキスト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TimeBreakText.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/
const D3DXVECTOR3 TimeBreakText::InitPositionUpper = { SCREEN_WIDTH * 1.5f, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::InitPositionLower = { SCREEN_WIDTH * -0.5f, 720.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::PositionUpper = { SCREEN_CENTER_X, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::PositionLower = { SCREEN_CENTER_X, 720.0f, 0.0f };

const D3DXVECTOR3 TimeBreakText::LastPositionUpper = { SCREEN_WIDTH * -0.5f, 240.0f, 0.0f };
const D3DXVECTOR3 TimeBreakText::LastPositionLower = { SCREEN_WIDTH * 1.5f, 720.0f, 0.0f };

/**************************************
コンストラクタ
***************************************/
TimeBreakText::TimeBreakText()
{
	upper = new Polygon2D();
	lower = new Polygon2D();

	upper->LoadTexture("data/TEXTURE/TimeBreak.png");
	lower->LoadTexture("data/TEXTURE/TimeBreak.png");

	upper->SetActive(false);
	lower->SetActive(false);
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

}

/**************************************
テキストイン終了コールバック
***************************************/
void TimeBreakText::OnFinishIn()
{
}

/**************************************
テキストアウト終了コールバック
***************************************/
void TimeBreakText::OnFinishOut()
{
}
