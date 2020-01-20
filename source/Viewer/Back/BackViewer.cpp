//=====================================
//
//BackViewer.cpp
//機能:背景UIビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackViewer.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BackViewer::BackViewer()
{
}

/**************************************
デストラクタ
***************************************/
BackViewer::~BackViewer()
{
}

/**************************************
描画処理
***************************************/
void BackViewer::Draw()
{
}

/**************************************
TimeBreak再生処理
***************************************/
void BackViewer::PlayTimeBreak()
{
	Tween::Move(*viewerContainer[TimeBreakUpper], InitPositionUpper, PositionUpper, 60, EaseType::OutCubic, true, []()
	{

	});
}
