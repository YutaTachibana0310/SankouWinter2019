//=====================================
//
//RankingViewer.cpp
//機能:ランキングビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RankingViewer.h"
#include "RankingText.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
RankingViewer::RankingViewer()
{
	const unsigned int RankingMax = 5;
	rankingContainer.reserve(RankingMax);

	D3DXVECTOR3 textPosition = { 0.0f, 300.0f, 0.0f };
	const float Offset = 100.0f;

	for (unsigned int i = 0; i < RankingMax; i++)
	{
		RankingText *ptr = new RankingText();
		ptr->SetPosition(textPosition);

		textPosition += Vector3::Up * Offset;

		rankingContainer.push_back(ptr);
	}
}

/**************************************
デストラクタ
***************************************/
RankingViewer::~RankingViewer()
{
	Utility::DeleteContainer(rankingContainer);
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
