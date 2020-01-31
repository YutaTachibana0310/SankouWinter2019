//=====================================
//
//ScoreRanking.cpp
//�@�\:�X�R�A�����L���O
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ScoreRanking.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../../Library/nameof/nameof.hpp"
#include "../GameConfig.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ScoreRanking::ScoreRanking()
{
	scoreContainer.reserve(RankingInfo::RankingMax);
	const std::string BaseSaveKey = std::string(NAMEOF_ENUM(GameConfig::SaveKey::Ranking));
	for (unsigned int i = 0; i < RankingInfo::RankingMax; i++)
	{
		std::string saveKey = BaseSaveKey;
		saveKey += std::to_string(i);

		const unsigned int score = PlayerPrefs::GetNumber<unsigned int>(saveKey);

		if (score != 0)
			scoreContainer.push_back(RankingInfo(i + 1, score, false));
		else
			scoreContainer.push_back(RankingInfo(i + 1, 20000 * (RankingInfo::RankingMax - i), false));
	}
}

/**************************************
�f�X�g���N�^
***************************************/
ScoreRanking::~ScoreRanking()
{
}

/**************************************
�X�V�m�F
***************************************/
void ScoreRanking::CheckUpdate()
{
	std::string KeyCurrentScore = std::string(NAMEOF_ENUM(GameConfig::SaveKey::CurrentScore));
	const unsigned int currentScore = PlayerPrefs::GetNumber<unsigned int>(KeyCurrentScore);

	for (auto itr = scoreContainer.begin(); itr != scoreContainer.end(); ++itr)
	{
		if (itr->Score() > currentScore)
			continue;

		int rank = std::distance(scoreContainer.begin(), itr);
		RankingInfo info = RankingInfo(rank, currentScore, true);

		auto insert = scoreContainer.insert(itr, info);
		scoreContainer.erase(scoreContainer.end() - 1, scoreContainer.end());
		break;
	}

	const std::string BaseSaveKey = std::string(NAMEOF_ENUM(GameConfig::SaveKey::Ranking));
	for (unsigned int i = 0; i < scoreContainer.size(); i++)
	{
		std::string saveKey = BaseSaveKey;
		saveKey += std::to_string(i);

		PlayerPrefs::SaveNumber<unsigned int>(saveKey, scoreContainer[i].Score());
	}

	for (unsigned int i = 0; i < scoreContainer.size(); i++)
	{
		scoreContainer[i] = RankingInfo(i + 1, scoreContainer[i].Score(), scoreContainer[i].IsPlayerScore());
	}
}

/**************************************
�����L���O�擾����
***************************************/
std::vector<RankingInfo> ScoreRanking::GetRanking()
{
	return scoreContainer;
}
