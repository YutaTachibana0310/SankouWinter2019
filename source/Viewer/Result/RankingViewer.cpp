//=====================================
//
//RankingViewer.cpp
//機能:ランキングビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RankingViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "RankingText.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
RankingViewer::RankingViewer()
{
	rankingContainer.reserve(RankingInfo::RankingMax);

	const D3DXVECTOR3 InitPosition = { 10.0f, 350.0f, 0.0f };
	const D3DXVECTOR3 Offset = { 30.0f, (float)RankingText::SizeFont * 1.6f , 0.0f };
	D3DXVECTOR3 textPosition = InitPosition;

	for (unsigned int i = 0; i < RankingInfo::RankingMax; i++)
	{
		if (i == RankingInfo::RankingMax / 2)
		{
			textPosition = InitPosition;
			textPosition.x += SCREEN_CENTER_X;
		}

		RankingText *ptr = new RankingText();
		ptr->SetPosition(textPosition);

		textPosition += Offset;

		rankingContainer.push_back(ptr);
	}

	caption = new Polygon2D();
	caption->SetSize({ 400.0f, 100.0f });
	caption->SetPosition({ SCREEN_CENTER_X, 100.0f, 0.0f });
	caption->LoadTexture("data/TEXTURE/Viewer/Ranking.png");
}

/**************************************
デストラクタ
***************************************/
RankingViewer::~RankingViewer()
{
	Utility::DeleteContainer(rankingContainer);
	SAFE_DELETE(caption);
}

/**************************************
更新処理
***************************************/
void RankingViewer::Update()
{
}

/**************************************
描画処理
***************************************/
void RankingViewer::Draw()
{
	caption->Draw();

	for (auto&& ranking : rankingContainer)
	{
		ranking->Draw();
	}
}

/**************************************
ランキング設定処理
***************************************/
void RankingViewer::SetRanking(const std::vector<RankingInfo>& ranking)
{
	const unsigned int MaxRanking = rankingContainer.size();
	for (unsigned int i = 0; i < MaxRanking; i++)
	{
		rankingContainer[i]->SetScore(ranking[i]);
	}
}
