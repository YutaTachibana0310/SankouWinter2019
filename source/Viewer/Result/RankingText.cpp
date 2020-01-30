//=====================================
//
//RankingText.cpp
//機能:ランキングテキスト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RankingText.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Task/TaskManager.h"

#include "../../System/RankingInfo.h"

/**************************************
コンストラクタ
***************************************/
RankingText::RankingText() :
	TextViewer("マキナス 4 Square", 80)
{
	SetHorizontalAlignment(HorizontalAlignment::Left);
}

/**************************************
デストラクタ
***************************************/
RankingText::~RankingText()
{
}

/**************************************
移動処理
***************************************/
void RankingText::MoveIn(float delay)
{
	const float OffsetX = -3000.0f;
	const D3DXVECTOR3 currentPosition = transform->GetPosition();

	transform->Move(Vector3::Left * OffsetX);

	if(delay == 0.0f)
		Tween::Move(*this, currentPosition, 60.0f, EaseType::OutCubic, true);
	else
	{
		TaskManager::Instance()->CreateDelayedTask(delay, true, [this, currentPosition]()
		{
			Tween::Move(*this, currentPosition, 60.0f, EaseType::OutCubic, true);
		});
	}
}

/**************************************
情報設定処理
***************************************/
void RankingText::SetScore(const RankingInfo & info)
{
	std::string rankingText = "";

	const int Rank = info.Rank();

	if (Rank == 1)
		rankingText += "1st ";
	else if (Rank == 2)
		rankingText += "2nd ";
	else if (Rank == 3)
		rankingText += "3rd ";
	else
	{
		rankingText += std::to_string(Rank);
		rankingText += "th ";
	}

	rankingText += std::to_string(info.Score());
	rankingText += " ";

	if (info.IsPlayerScore())
	{
		rankingText += "YOU!!";
		SetColor(D3DXCOLOR(255.0f, 100.0f, 100.0f, 255.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
	}

	SetText(rankingText);

}
