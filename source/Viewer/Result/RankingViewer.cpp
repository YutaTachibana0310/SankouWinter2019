//=====================================
//
//RankingViewer.cpp
//�@�\:�����L���O�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RankingViewer.h"
#include "RankingText.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
RankingViewer::RankingViewer()
{
	rankingContainer.reserve(RankingInfo::RankingMax);

	D3DXVECTOR3 textPosition = { 0.0f, 300.0f, 0.0f };
	const float Offset = (float)RankingText::SizeFont;

	for (unsigned int i = 0; i < RankingInfo::RankingMax; i++)
	{
		RankingText *ptr = new RankingText();
		ptr->SetPosition(textPosition);

		textPosition += Vector3::Up * Offset;

		rankingContainer.push_back(ptr);
	}
}

/**************************************
�f�X�g���N�^
***************************************/
RankingViewer::~RankingViewer()
{
	Utility::DeleteContainer(rankingContainer);
}

/**************************************
�X�V����
***************************************/
void RankingViewer::Update()
{
}

/**************************************
�`�揈��
***************************************/
void RankingViewer::Draw()
{
	for (auto&& ranking : rankingContainer)
	{
		ranking->Draw();
	}
}

/**************************************
�����L���O�ݒ菈��
***************************************/
void RankingViewer::SetRanking(const std::vector<RankingInfo>& ranking)
{
	const unsigned int MaxRanking = rankingContainer.size();
	for (unsigned int i = 0; i < MaxRanking; i++)
	{
		rankingContainer[i]->SetScore(ranking[i]);
	}
}
