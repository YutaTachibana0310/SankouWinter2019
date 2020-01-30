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
static変数
***************************************/
const int RankingText::SizeFont = 100;

/**************************************
コンストラクタ
***************************************/
RankingText::RankingText() :
	TextViewer("マキナス 4 Square", SizeFont)
{
	SetHorizontalAlignment(HorizontalAlignment::Left);
	UseOutLine(true);
	SetOutlineColor(D3DXCOLOR(0.5f, 0.8f, 1.0f, 1.0f));
	SetOutlineWidth(3);

	scoreText = new TextViewer("マキナス 4 Square", SizeFont);

	AddChild(scoreText);
	scoreText->SetLocalPosition({ 250.0f, 0.0f, 0.0f });
	scoreText->SetHorizontalAlignment(HorizontalAlignment::Left);
	scoreText->UseOutLine(true);
	scoreText->SetOutlineColor(D3DXCOLOR(0.5f, 0.8f, 1.0f, 1.0f));
	scoreText->SetOutlineWidth(3);
}

/**************************************
デストラクタ
***************************************/
RankingText::~RankingText()
{
	SAFE_DELETE(scoreText);
}

/**************************************
描画処理
***************************************/
void RankingText::Draw()
{
	scoreText->Draw();
	TextViewer::Draw();
}

/**************************************
移動処理
***************************************/
void RankingText::MoveIn(float delay)
{
	const float OffsetX = -3000.0f;
	const D3DXVECTOR3 currentPosition = transform->GetPosition();

	transform->Move(Vector3::Right * OffsetX);

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
		rankingText += "1st";
	else if (Rank == 2)
		rankingText += "2nd";
	else if (Rank == 3)
		rankingText += "3rd";
	else
	{
		rankingText += std::to_string(Rank);
		rankingText += "th";
	}

	std::string score = std::to_string(info.Score());

	if (info.IsPlayerScore())
	{
		score += "YOU!!";
		SetColor(D3DXCOLOR(255.0f, 100.0f, 100.0f, 255.0f));
		scoreText->SetColor(D3DXCOLOR(255.0f, 100.0f, 100.0f, 255.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
		scoreText->SetColor(D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
	}

	SetText(rankingText);
	scoreText->SetText(score);
}
